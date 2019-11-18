HOME = /home/rrzhang
LDFLAGS += -L$(HOME)/.local/protobuf/lib/ -lprotobuf -L$(HOME)/.local/grpc/lib -lprotobuf -lgrpc++ -lgrpc -lgrpc++_reflection -Wl,--as-needed

CLIENT_PRE = os_rpc.pb.o os_rpc.grpc.pb.o main.o client.o

client : $(CLIENT_PRE)
	gcc  $(CLIENT_PRE) $(LDFLAGS) -lstdc++ -o client

client.o : client.cpp
	g++ -c client.cpp --std=c++11

main.o : main.c
	gcc -c main.c

os_rpc.pb.o : ../pb/os_rpc.pb.cc
	g++ -c ../pb/os_rpc.pb.cc --std=c++11 -o os_rpc.pb.o

os_rpc.grpc.pb.o : ../pb/os_rpc.grpc.pb.cc
	g++ -c ../pb/os_rpc.grpc.pb.cc --std=c++11 -o os_rpc.grpc.pb.o

clean:
	rm -f *.o ../pb/*.o
