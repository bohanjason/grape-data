mpiexec.hydra -n 2 $GRAPE_HOME/build/lda --nointeractive \
				    --v 2 \
                                    --result_dir $GRAPE_HOME/build \
				    --query_dir grape-data/test/lda-query \
			 	    --vfile $GRAPE_HOME/../dataset/daily_kos/tokens/daily_kos.v \
                                    --efile $GRAPE_HOME/../dataset/daily_kos/tokens/daily_kos.e \
                                    --rfile $GRAPE_HOME/../dataset/daily_kos/tokens/daily_kos.r \
                                    --max_iteration 10                         
          #--enable_assemble true \

				   # --nfrag 10
                                   # --prefetch_hops 2 \


