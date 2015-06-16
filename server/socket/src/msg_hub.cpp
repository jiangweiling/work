#include "msg_hub.h"
namespace socket_ns {

MsgHub MsgHub::msghub;
bool MsgHub::initial = false;

MsgHub::MsgHub()=default;

MsgHub& MsgHub::operator= (MsgHub&& mh) {
	//cerr<<"MsgHub& MsgHub::operator= (MsgHub&& mh)\n";
	//cerr<<"MsgHub& MsgHub::operator= (MsgHub&& mh)exit\n";
	return *this;
}

MsgHub& MsgHub::get_msghub(){
	//cerr<<"MsgHub& MsgHub::get_msghub()\n";
	if(!initial){
		msghub = move(MsgHub());
		initial = true;
	}
	//cerr<<"MsgHub& MsgHub::get_msghub()exit\n";
	return msghub;
}

vector<Socket> MsgHub::push(vector<Socket> ss) {
	//cerr<<"void MsgHub::push(const vector<Socket>& ss)\n";
	unique_lock<mutex> lck(m_mutex);
	vector<Socket> ret;
	ret.reserve(ss.size());
	for(auto& s : ss){
		string data;
		if(!s.recv(data)){
			cout<<"disconnect from "<<s<<endl;
			m_ss_umap.erase(s.get_fd());
			ret.push_back(s);
		}
		else{
			cout<<"msg from "<<s<<endl;
			cout<<"data:"<<data<<endl;
		}
	}
	return move(ret);
	//cerr<<"void MsgHub::push(const vector<Socket>& ss)exit\n";
}

};
