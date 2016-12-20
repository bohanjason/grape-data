#!/usr/bin/python
import sys
import os
import subprocess

# programs = {
#     # From the mpi-hello-world tutorial
#     'sample': ('mpi_sample', 4),
#     'cc': ('mpi_cc', 4),
#     'sim': ('mpi_sim', 4),
#     'sssp': ('mpi_sssp', 4),
#     'vf2': ('mpi_vf2', 4),
#     'kws': ('mpi_kws', 4),
# }

#config
output_dir_in_local = "output"
output_dir_in_cluster = "~/temp"
host_file = "conf/worker_host"
max_num_worker = 5


programs = {'sample','cc','sim','sssp','vf2','kws'}

print "para: program num_workers cluster_mode [output_filename]"
print "e.g.: sssp 4 0"
print "e.g.: sssp 4 1 sssp.out"

program_to_run = sys.argv[1] if len(sys.argv) > 1 else None
num_workers = sys.argv[2] if len(sys.argv) > 2 else None
cluster_mode = sys.argv[3] if len(sys.argv) > 3 else None
output_file = sys.argv[4] if len(sys.argv) > 4 else None
if len(sys.argv) < 4:
    print "at least 3 parameters."
elif not program_to_run in programs:
    print 'Must enter program name to run. Possible programs are: {0}'.format(list(programs))
elif not (num_workers.isdigit() and int(num_workers) <= max_num_worker and int(num_workers) > 0 ):
    print 'Worker number must be digit and should be in the range of 1 - {0}'.format(max_num_worker);
else:
    # Try to compile before running
    subprocess.call(['make clean && make config && make ./build/{0}'.format(program_to_run)], shell=True)
    if cluster_mode == '0':
        cluster_mode = None
    
    print '########## finish compile and build executable files ##########'

    mpirun = os.environ.get('MPIRUN', 'mpirun')
    hosts = '' if not cluster_mode else '--hostfile {0}'.format(host_file)
    outdir = output_dir_in_local if not cluster_mode else output_dir_in_cluster

    if output_file and not os.path.exists(outdir):
        os.makedirs(outdir)

    out_suf = '' if not output_file else '> {0}/{1}'.format(outdir,output_file)

    sys_call = '{0} -n {1} {2} -x CLASSPATH=`hadoop classpath` ./build/{3} {4}'.format(
        mpirun, num_workers, hosts, program_to_run, out_suf)


    # sys_call = 'sudo {0} -n {1} xterm -e gdb {2} ./build/{3} 10 > kws.out'.format(
    #     mpirun, programs[program_to_run][1], hosts, program_to_run)

#    sys_call = '{0} -n {1} {2} -x CLASSPATH=`hadoop classpath` /home/ubuntu/grape/cpp/build/{3} 1 > sssp.out'.format(
 #       mpirun, programs[program_to_run][1], hosts, program_to_run)


    print sys_call
    subprocess.call([sys_call], shell=True)
