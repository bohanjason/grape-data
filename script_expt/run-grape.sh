#!/usr/bin/env sh
if [ $# -lt 4 ]
then
    echo "param1 algorithm: bfs, cc, sim, vf2, cf, sssp"
	echo "param2 dataset: movie, twitter, livejournal, dbpedia"
	echo "param3 location: hdfs, local, localgz"
	echo "param4 numWorker: 4, 8,... 16"
	exit
fi

# config
fragEachWork=4
verbose="--v 2"
# cmakelist flags
export CXXFLAGS=-DCMAKE_BUILD_TYPE=Release

####################################################################################

if [ -z "$GRAPE_HOME" ]; then
	echo "source grape.env first."
	exit
fi

algorithm=$1 #bfs, cc, sim, vf2, 
dataset=$2 #movie, twitter, livejournal, dbpedia
location=$3 #hdfs, local, localgz
numWorker=$4

DATE=`date +%Y%m%d-%H%M%S`

numFrag=`expr $numWorker \* $fragEachWork`
numProcs=`expr $numWorker + 1`
gzipEnable=""


resultPath="/home/grape/crdataset/exp_result/${algorithm}/${location}_${dataset}_n${numWorker}_${DATE}"
log="/home/grape/crdataset/exp_log/${algorithm}/${location}_${dataset}_n${numWorker}_${DATE}"
query_dir="/home/grape/crdataset/grape-data/exp_query/${algorithm}/${dataset}/run"

mkdir -p $resultPath
mkdir -p $log

# config

if [ $dataset = "movie" ] && [ $location != "hdfs" ]; then
	vfile="/home/grape/crdataset/dataset/movie/movie.v"
 	efile="/home/grape/crdataset/dataset/movie/movie.e"
 	rfile="/home/grape/crdataset/dataset/movie/movie.r"$numFrag
 	fileSource=0
fi

if [ $dataset = "twitter" ] && [ $location != "hdfs" ]; then
	vfile="/home/grape/crdataset/dataset/twitter.v"
	efile="/home/grape/crdataset/dataset/twitter.e"
	rfile="/home/grape/crdataset/dataset/twitter.r"
	fileSource=0
fi

if [ $dataset = "livejournal" ] && [ $location != "hdfs" ]; then
	vfile="/home/grape/crdataset/dataset/livejournal.v"
	efile="/home/grape/crdataset/dataset/livejournal.e"
	rfile="/home/grape/crdataset/dataset/livejournal.r"$numFrag
	fileSource=0
fi

if [ $dataset = "dbpedia" ] && [ $location != "hdfs" ]; then
	vfile="/home/grape/crdataset/dataset/dbpedia-l10-law28.v"
	efile="/home/grape/crdataset/dataset/dbpedia.e"
	rfile="/home/grape/crdataset/dataset/dbpedia.r"$numFrag
	fileSource=0
fi

# dataset with gz enable.
if [ $location = "localgz" ]; then
	vfile="${vfile}.gz"
	efile="${efile}.gz"
	rfile="${rfile}.gz"
	gzipEnable="--gzip true"
fi

# dataset load from hdfs
if [ $dataset = "movie" ] && [ $location = "hdfs" ]; then
	vfile="/dataset/movie/movie.v"
 	efile="/dataset/movie/movie.e"
 	rfile="/dataset/movie/movie.r"$numFrag
 	fileSource=1
fi

if [ $dataset = "twitter" ] && [ $location = "hdfs" ]; then
	vfile="/dataset/twitter.v"
	efile="/dataset/twitter.e"
	rfile="/dataset/twitter.r"
	fileSource=1
fi

if [ $dataset = "livejournal" ] && [ $location = "hdfs" ]; then
	vfile="/dataset/livejournal.v"
	efile="/dataset/livejournal.e"
	rfile="/dataset/livejournal.r"$numFrag
	fileSource=1
fi

if [ $dataset = "dbpedia" ] && [ $location = "hdfs" ]; then
	vfile="/dataset/dbpedia-l10-law28.v"
	efile="/dataset/dbpedia.e"
	rfile="/dataset/dbpedia.r"$numFrag
	fileSource=1
fi


# cp files
cp $GRAPE_HOME/cpp/conf/machines_$numWorker $GRAPE_HOME/cpp/conf/workers

# build
cd $GRAPE_HOME/cpp
cd build
cmake ..
make $algorithm -j8 

# cd to home and rsync
cd $GRAPE_HOME/cpp
DONE=false
until $DONE; do
    read host || DONE=true
    if [ "$host" != "" ]; then
    	echo "copy grape file to host:$host"
    	rsync -a build $host:$GRAPE_HOME/cpp
    fi
done < "$GRAPE_HOME/cpp/conf/workers"

# return back and run
cd $GRAPE_HOME/cpp

echo "mpiexec.hydra -n ${numProcs} --hostfile ./conf/workers ./build/$algorithm --vfile ${vfile} --efile ${efile} --rfile ${rfile} --nfrag ${numFrag} --file_location ${fileSource} --log_dir ${log} --result_dir ${resultPath} --query_dir ${query_dir} --nointeractive ${verbose} ${gzipEnable}"
mpiexec.hydra -n ${numProcs} --hostfile ./conf/workers ./build/$algorithm --vfile ${vfile} --efile ${efile} --rfile ${rfile} --nfrag ${numFrag} --file_location ${fileSource} --log_dir ${log} --result_dir ${resultPath} --query_dir ${query_dir} --nointeractive ${verbose} ${gzipEnable}
