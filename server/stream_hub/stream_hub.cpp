#include "stream_hub.h"

namespace socket_ns {

StreamHub StreamHub::hub;
bool StreamHub::initial = false;

StreamHub::StreamHub()=default;

StreamHub& StreamHub::operator= (StreamHub&& sh) {
	//cerr<<"StreamHub& StreamHub::operator= (StreamHub&& mh)\n";
	//cerr<<"StreamHub& StreamHub::operator= (StreamHub&& mh)exit\n";
	return *this;
}

StreamHub& StreamHub::get_hub(){
	//cerr<<"StreamHub& StreamHub::get_hub()\n";
	if(!initial){
		hub = move(StreamHub());
		initial = true;
	}
	//cerr<<"StreamHub& StreamHub::get_hub()exit\n";
	return hub;
}

vector<Socket> StreamHub::push(vector<Socket> ss) {
	//cerr<<"void StreamHub::push(const vector<Socket>& ss)\n";
	unique_lock<mutex> lck(m_mutex);
	vector<Socket> disconnect;
	disconnect.reserve(ss.size());
	for(auto& s : ss){
		string data;
		if(!s.recv(data)){
			cout<<"disconnect from "<<s<<endl;
			m_ss_umap.erase(s.get_fd());
			disconnect.push_back(s);
		}
		else{
			if(m_ss_umap.end() != m_ss_umap.find(s.get_fd())) {
				string& msg_stream = m_ss_umap[s.get_fd()];
				msg_stream.append(move(data));
			}
			else{
				m_ss_umap[s.get_fd()] = move(data);
			}
		}
	}
	//cerr<<"void StreamHub::push(const vector<Socket>& ss)exit\n";
	return move(disconnect);
}
};
