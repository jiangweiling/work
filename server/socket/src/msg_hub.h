#ifndef MSG_HUB_H
#define MSG_HUB_H
#include "socket_ns.h"
#include "socket.h"

namespace socket_ns {

typedef unordered_map<int,queue<string>> SocketStrUmap;
class MsgHub {
private:
	static MsgHub msghub;
	static bool initial;
	SocketStrUmap m_ss_map;
	mutex m_mutex;
private:
	MsgHub()=default;
	MsgHub(MsgHub&& mh);
	MsgHub& operator= (MsgHub&& mh);
public:
	MsgHub(const MsgHub& mh)=delete;
	MsgHub& operator= (const MsgHub& mh)=delete;
	static MsgHub& get_msghub();
	vector<Socket> push(vector<Socket> ss);
	int run();
};


};

#endif
