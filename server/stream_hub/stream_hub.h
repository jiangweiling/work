#ifndef STREAM_HUB_H
#define STREAM_HUB_H
#include "socket_ns.h"
#include "socket.h"

namespace socket_ns {

class StreamHub {
private:
	static StreamHub hub;
	static bool initial;
	SocketStrUmap m_ss_umap; // typedef in socket_ns.h
	mutex m_mutex;
private:
	StreamHub();
	StreamHub& operator= (StreamHub&& sh);
public:
	StreamHub(const StreamHub& sh)=delete;
	StreamHub& operator= (const StreamHub& sh)=delete;
	static StreamHub& get_hub();
	vector<Socket> push(vector<Socket> ss); // return sockets that closed by clients
	int run();
};


};

#endif
