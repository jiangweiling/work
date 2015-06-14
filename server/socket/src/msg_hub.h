#ifndef MSG_HUB_H
#define MSG_HUB_H
#include "socket_ns.h"
#include "socket.h"

namespace socket_ns {

typedef struct socket_hash_{
	hash<int> int_hash;
	size_t operator()(const Socket& s){
		return int_hash(s.get_fd());
	}
}socket_hash;

typedef struct socket_equal_{
	bool operator()(const Socket& lhs, const Socket& rhs){
		return lhs.get_fd() == rhs.get_fd();
	}
}socket_equal;

typedef unordered_map<Socket, queue<string>, socket_hash, socket_equal> SocketStrUmap;

class MsgHub {
private:
	static MsgHub msghub;
	static bool initial;
	//SocketStrUmap m_msg_umap;
	mutex m_mutex;
private:
	MsgHub()=default;
	MsgHub(MsgHub&& mh);
	MsgHub& operator= (MsgHub&& mh);
public:
	MsgHub(const MsgHub& mh)=delete;
	MsgHub& operator= (const MsgHub& mh)=delete;
	static MsgHub& get_msghub();
	void push(const vector<Socket>& ss);
	int run();
};


};

#endif
