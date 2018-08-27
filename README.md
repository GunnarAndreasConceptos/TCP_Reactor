# TCP_Reactor
Experiment with event driven REACTOR design pattern for C
Basically this program http://www.adampetersen.se/Patterns%20in%20C%205,%20REACTOR.pdf
It runs a TCP server on a specified port and prints out TCP data from connected clients.

# Compile
Compile with a the following command
```
make
```


# Run
Launch with the following
```
cd bin
tcp_reactor -p port
```
If no port number is given a default port number is used and displayed during runtime.

To add a client run the following command in another terminal window
```
netcat localhost port
```
Where port is changed the port number from the server.

After client has connected, simply type in the netcat terminal and see the results show up on the server when pressing enter.

# Example
Terminal 1:
```
cd bin
tcp_reactor -p 5006
```

Terminal 2:
```
netcat localhost 5006
```

# Testing
Testing is done using ceedling. Run the tests by doing the following:
```
cd test_TCP_Reactory
ceedling
```