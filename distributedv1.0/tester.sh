#g++ -std=c++17 -g -I /usr/local/include/boost max_flow_boost.cpp -o testing_serial.out

mpic++ -std=c++17 -Wshadow -Wall -o a.out sample_mpi.cpp -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
mpirun -np 2 --oversubscribe a.out