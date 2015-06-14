#include "msg_hub.h"
namespace socket_ns {

MsgHub MsgHub::msghub;
bool MsgHub::initial = false;

MsgHub::MsgHub(MsgHub&& mh) {
	cerr<<"MsgHub::MsgHub(MsgHub&& mh)\n";
	cerr<<"MsgHub::MsgHub(MsgHub&& mh)exit\n";
}

MsgHub& MsgHub::operator= (MsgHub&& mh) {
	cerr<<"MsgHub& MsgHub::operator= (MsgHub&& mh)\n";
	cerr<<"MsgHub& MsgHub::operator= (MsgHub&& mh)exit\n";
	return *this;
}

MsgHub& MsgHub::get_msghub(){
	cerr<<"MsgHub& MsgHub::get_msghub()\n";
	if(!initial){
		msghub = move(MsgHub());
		initial = true;
	}
	cerr<<"MsgHub& MsgHub::get_msghub()exit\n";
	return msghub;
}

void MsgHub::push(const vector<Socket>& ss) {
	cerr<<"void MsgHub::push(const vector<Socket>& ss)\n";
	lock_guard<mutex> lck(m_mutex);
	for(auto s : ss){
		cout<<s<<endl;
	}
	cerr<<"void MsgHub::push(const vector<Socket>& ss)exit\n";
}

};
