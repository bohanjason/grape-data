mpiexec.hydra -n 1 $GRAPE_HOME/build/vf2 --nointeractive \
				    --query_dir grape-data/test/vf2-query \
				    --result_dir $GRAPE_HOME/build \
				    --v 2 \
			 	    --vfile $GRAPE_HOME/../dataset/twitter/twitter.v \
                                    --efile $GRAPE_HOME/../dataset/twitter/twitter.e \
                                    --rfile $GRAPE_HOME/../dataset/twitter/twitter.r 
                                   # --prefetch_hops 2 \
                                   # --enable_assemble true
