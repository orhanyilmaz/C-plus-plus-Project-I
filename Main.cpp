#include<iostream>
#include<fstream>
#include<string.h>
#include<cstdlib>
#include <windows.h>

using namespace std;

struct post{
public:
	string id;
	string text;
	int height;
	int width;
	string liked[100];
	int like_count;
	string reposted[100];
};
struct node{
public:
	string user;
	string personal_comment;
	string followeds[100];
	int post_count;
	int followed_count;
	string blocked[100];
	int blocked_count;
	struct post post[100];
	struct node *next;
};
class List{                    					  // It's my list..
	public:
	node *head;                   			  // linked list..
	node *last;					  			 //linked list..
	List();
	void AddUser(ifstream &,ofstream &);
	void FollowUser(ifstream &,ofstream &);
	void AddPost(ifstream &,ofstream &);
	void LikePost(ifstream &,ofstream &);
	void ViewUser(ifstream &,ofstream &);
	void Repost(ifstream &,ofstream &);
	void BlockUser(ifstream &,ofstream &);
	void UnfollowUser(ifstream &,ofstream &);
};
List::List(){
	head=NULL;
	last=NULL;
}

void List::AddUser(ifstream & file_i,ofstream & file_o){
		string text;
		node *temp=new node;
		getline(file_i,text,' ');
		struct node *current;
		current = head;
		while(current!=NULL){                    		  					// while for visit all node..
			if(text==current->user){											// checking user already created..
				cout<<"Err: The user '"<<text<<"' has already been created"<<endl;
				file_o<<"Err: The user '"<<text<<"' has already been created"<<endl;
				getline(file_i,text);												// then personal comment skipping..
				return;
			}
			current=current->next;
		}
		temp->user=text;								//adding new user..
		getline(file_i,text);

		temp->next=NULL;
		temp->personal_comment=text;					//adding user's comment.
		if(head == NULL){
			        head = temp;
			    }else{
			        last->next = temp;
			    }
			    last = temp;
		cout<<"User '"<< temp->user << "' has been created"<<endl;
		file_o<<"User '"<< temp->user << "' has been created"<<endl;
}

void List::FollowUser(ifstream & file_i,ofstream & file_o){
	string text1,text2;
	int check_username1=0,check_username2=0,check_followed=0;
	getline(file_i,text1,' ');
	getline(file_i,text2);
	struct node *current;
	current=head;
	while(current!=NULL){							// while for visit all node..
		if(text2==current->user){
			for(int i=0 ;i<100 ;i++){
				if(current->blocked[i].compare(text1)==0){										// checking user had blocekd..
				cout<<"Err: the user '"<<current->user<<"' had blocked '"<<text1<<"'"<<endl;
				file_o<<"Err: the user '"<<current->user<<"' had blocked '"<<text1<<"'"<<endl;
				return;
				}
			}
		}

		current=current->next;
	}
	if(text1==text2){													// cheking usernames are equal..
			cout<<"Err: "<<text1<<" cannot follow itself!"<<endl;
			file_o<<"Err: "<<text1<<" cannot follow itself!"<<endl;
			return;
	}

	current = head;
	while(current!=NULL){                    		  					// while for visit all node..
		if(text1==current->user){											// checking user1 ..
			check_username1=1;

			for(int i=0 ; i<100 ; i++){
			if(current->followeds[i].compare(text2)== 0){										//checking user already followed..
				check_followed=1;
				cout<<"Err: "<<text1<<" has already followed "<<text2<<"!"<<endl;
				file_o<<"Err: "<<text1<<" has already followed "<<text2<<"!"<<endl;
			}
			}
		}
		if(text2==current->user)											// checking user2 ..
				check_username2=1;

		current=current->next;
	}

	if(check_username1==1 && check_username2==1 && check_followed!=1 ){
		current = head;
		while(current!=NULL){                    		  					// while for visit all node..
			if(text1==current->user){
				for(int i=0 ; i<100 ; i++){
				if(current->followeds[i].compare("") ==0){                // finding empty array ..
					current->followeds[i]=text2;								//taking username2 for followed info..
					current->followed_count++;									//increase followed_count..
					cout<<current->user<<" followed "<<current->followeds[i]<<endl;
					file_o<<current->user<<" followed "<<current->followeds[i]<<endl;
					return;
				}
				}
			}
			current=current->next;
			}
	}
	if(check_username1==0){
		cout<<"Err: the user '"<<text1<<"' could not be found!"<<endl;
		file_o<<"Err: the user '"<<text1<<"' could not be found!"<<endl;
	}
	if(check_username2==0){
		cout<<"Err: the user '"<<text2<<"' could not be found!"<<endl;
		file_o<<"Err: the user '"<<text2<<"' could not be found!"<<endl;
	}
}

void List::AddPost(ifstream & file_i,ofstream & file_o){
	string text;
	int check_user=0;
	getline(file_i,text,' ');
	struct node *current;
	current = head;
	while(current!=NULL){                    		  					// while for visit all node..
		if(text==current->user){											// checking user already taken..
			current->post_count++;
			check_user=1;
			getline(file_i,text,' ');
			for(int i=0 ;i<100 ; i++){
				if(current->post[i].id.compare("") ==0){
				current->post[i].id=text;
				break;
				}
			}
			getline(file_i,text);
			int check_image=0;
			for(int i=0 ; i<(int)text.length();i++){

				if(text[i]==' '){
					check_image=1;
					char text_[100];
					strncpy(text_, text.c_str(), sizeof(text_));
					text_[sizeof(text_) - 1] = 0;
					const char * separator = " ";
					char * word1 = strtok(text_, separator);
					for(int j=0 ; j<100 ; j++){
						if(current->post[j].text.compare("") ==0){
							current->post[j].text=word1;
							char * word2 = strtok(NULL, "");
							char * word3 = strtok(word2, "x");
							current->post[j].width=atoi(word3);
							char * word4 = strtok(NULL, "");
							current->post[j].height=atoi(word4);
							return;
						}
					}
				}
			}
			if(check_image==0){
				for(int j=0 ; j<100 ; j++){
					if(current->post[j].text.compare("") ==0){
						current->post[j].text=text;
						current->post[j].height=0;
						current->post[j].width=0;
						return;
					}
				}
			}
		}
		current=current->next;
	}
	if(check_user==0){
		cout<<"Err: the user '"<<text<<"' could not be found!"<<endl;
		file_o<<"Err: the user '"<<text<<"' could not be found!"<<endl;
		getline(file_i,text,' ');
		getline(file_i,text);
	}
}

void List::LikePost(ifstream & file_i,ofstream & file_o){
	string text,text1,text2;
	int check_username1=0,check_username2=0,check_post_id=0,check_liked=0;
	getline(file_i,text1,' ');
	getline(file_i,text2,' ');
	struct node *current;
	current = head;
	while(current!=NULL){
			if(text2==current->user){
				for(int i=0 ;i<100 ;i++){
					if(current->blocked[i].compare(text1)==0){
					cout<<"Err: the user '"<<current->user<<"' had blocked '"<<text1
							<<"'. You cannot like a post of '"<<current->user<<"'!"<<endl;
					file_o<<"Err: the user '"<<current->user<<"' had blocked '"<<text1
							<<"'. You cannot like a post of '"<<current->user<<"'!"<<endl;
					getline(file_i,text);
					return;
					}
				}
			}

			current=current->next;
		}

	current = head;
	while(current!=NULL){                    		  					// while for visit all node..
		if(text2==current->user){											// checking user ..
			check_username2=1;
			getline(file_i,text);
			for(int i=0 ; i<100 ; i++){
			if(current->post[i].id.compare(text) ==0){
				check_post_id=1;
				break;
			}
			}
			if(check_post_id==0){
				cout<<"Err: "<<text1<<"'s post could not be found!"<<endl;
				file_o<<"Err: "<<text1<<"'s post could not be found!"<<endl;
			}
			for(int i=0 ;i<100 ; i++){
				if(current->post[i].id.compare(text)==0 ){
					for(int j=0 ;j<100;j++){
						if(current->post[i].liked[j].compare(text1)==0){
						check_liked=1;
						cout<<"Err: "<<text2<<"'s post had already been liked!"<<endl;
						file_o<<"Err: "<<text2<<"'s post had already been liked!"<<endl;
						break;
						}
					}
					}
				}
		}
		if(text1==current->user){											// checking user ..
			check_username1=1;
		}

			current=current->next;
	}
	if(check_username1==1 && check_username2==1 && check_post_id==1 && check_liked==0){
		current = head;
		while(current!=NULL){                    		  					// while for visit all node..
			if(text2==current->user){
				for(int i=0 ; i<100 ; i++){
				if(current->post[i].id.compare(text)==0){
					for(int j=0 ; j<100 ;j++){
					if(current->post[i].liked[j].compare("")==0){
					current->post[i].liked[j]=text1;
					cout<<current->post[i].liked[j]<<" has liked "<<current->user<<"'s post"<<endl;
					file_o<<current->post[i].liked[j]<<" has liked "<<current->user<<"'s post"<<endl;
					current->post[i].like_count++;
					return;
					}
					}
					}

				}
			}
			current=current->next;
			}
	}
	if(check_username1==0){
		cout<<"Err: "<<"the user '"<<text1<<"' could not be found!"<<endl;
		file_o<<"Err: "<<"the user '"<<text1<<"' could not be found!"<<endl;
	}
	if(check_username2==0){
		cout<<"Err: "<<"the user '"<<text2<<"' could not be found!"<<endl;
		file_o<<"Err: "<<"the user '"<<text2<<"' could not be found!"<<endl;
		getline(file_i,text);
	}
}

void List::ViewUser(ifstream & file_i,ofstream & file_o){
	string text ;
	int check_user=0;
	getline(file_i,text);
	struct node *current;
	current = head;
	while(current!=NULL){                    		  					// while for visit all node..
		if(text==current->user){											// checking user already taken..
			cout<<endl;
			file_o<<endl;

			cout<<"----------------------------------------------"<<endl;
			file_o<<"----------------------------------------------"<<endl;
			check_user=1;

			cout<<current->user<<" following ["<<current->followed_count<<"]"
			<<" - blocked ["<<current->blocked_count<<"] users - ["<<current->post_count<<"] posts"<<endl;

			file_o<<current->user<<" following ["<<current->followed_count<<"]"
			<<" - blocked ["<<current->blocked_count<<"] users - ["<<current->post_count<<"] posts"<<endl;

			cout<<current->personal_comment<<endl;
			file_o<<current->personal_comment<<endl;

			cout<<"--------------------Tweets--------------------"<<endl;
			file_o<<"--------------------Tweets--------------------"<<endl;

			for(int i=0 ; current->post[i].id.compare("")!= 0;i++){
				if(current->post[i].width==0){
				cout<<current->post[i].text<<" - Likes: "<<current->post[i].like_count<<endl;

				file_o<<current->post[i].text<<" - Likes: "<<current->post[i].like_count<<endl;
				}
				else{
					cout<<current->post[i].text<<" - TotalSize: ["<<
						(current->post[i].width)*(current->post[i].height) <<" pixels] - Likes: "<<current->post[i].like_count<<endl;

					file_o<<current->post[i].text<<" - TotalSize: ["<<
						(current->post[i].width)*(current->post[i].height) <<" pixels] - Likes: "<<current->post[i].like_count<<endl;
				}
			}
			cout<<"----------------------------------------------"<<endl;
			file_o<<"----------------------------------------------"<<endl;
		}
		current=current->next;
	}
	if(check_user==0){
		cout<<"Err: the user '"<<text<<"' could not be found!"<<endl;
		file_o<<"Err: the user '"<<text<<"' could not be found!"<<endl;
	}

}

void List::Repost(ifstream & file_i,ofstream & file_o){
	string text,text1,text2;
	int check_username1=0,check_username2=0,check_post_id=0, check_reposted=0;
	getline(file_i,text1,' ');
	getline(file_i,text2,' ');
	getline(file_i,text);

	if(text1==text2){
		cout<<text1<<" cannot repost own post!"<<endl;
		file_o<<text1<<" cannot repost own post!"<<endl;
		return;
	}

	struct node *current;

	current = head;
		while(current!=NULL){
				if(text2==current->user){
					for(int i=0 ;i<100 ;i++){
						if(current->blocked[i].compare(text1)==0){
						cout<<"Err: the user '"<<current->user<<"' had blocked '"<<text1
								<<"'. You cannot repost a post of '"<<current->user<<"'!"<<endl;
						file_o<<"Err: the user '"<<current->user<<"' had blocked '"<<text1
								<<"'. You cannot repost a post of '"<<current->user<<"'!"<<endl;
						getline(file_i,text);
						return;
						}
					}
				}

				current=current->next;
			}


	current = head;
	while(current!=NULL){                    		  					// while for visit all node..
		if(text2==current->user){											// checking user ..
			check_username2=1;
			for(int i=0 ; i<100 ; i++){
				if(current->post[i].id.compare(text)== 0){
					check_post_id=1;
					for(int j=0 ;j<100 ;j++){
						if(current->post[i].reposted[j]==text1){
							check_reposted=1;
							cout<<"Err: This post had already been reposted by '"<<text1<<"' !"<<endl;
							file_o<<"Err: This post had already been reposted by '"<<text1<<"' !"<<endl;
							return;
						}
					}
				}
			}
		}
		if(text1==current->user)											// checking user ..
				check_username1=1;

		current=current->next;
	}
	if(check_username1==1 && check_username2==1 && check_post_id==1 && check_reposted==0){
		current = head;
		struct node *current1;
		current1 = head;
		while(current!=NULL){
			if(text2==current->user){
				for(int i=0 ; i<100 ; i++){
					if(current->post[i].id.compare(text)== 0){
						while(current1!=NULL){
							if(text1==current1->user){
								for(int j=0 ; j<100 ; j++){
									if(current1->post[j].id.compare("")==0){
										current1->post[j].id=current->post[i].id;
										current1->post[j].text=current->post[i].text;
										current1->post[j].width=current->post[i].width;
										current1->post[j].height=current->post[i].height;
										current1->post_count++;
										break;
									}
								}
							}
							current1=current1->next;
						}
						for(int j=0 ;j<100; j++){
							if(current->post[i].reposted[j].compare("")==0){
								current->post[i].reposted[j]=text1;
								cout<<text1<<" has reposted "<<text2<<"'s post"<<endl;
								file_o<<text1<<" has reposted "<<text2<<"'s post"<<endl;
								return;
							}
						}
					}
				}

			}
			current=current->next;
		}
	}

	if(check_username1==0){
			cout<<"Err: "<<"the user '"<<text1<<"' could not be found!"<<endl;
			file_o<<"Err: "<<"the user '"<<text1<<"' could not be found!"<<endl;
		}
	if(check_username2==0){
			cout<<"Err: "<<"the user '"<<text2<<"' could not be found!"<<endl;
			file_o<<"Err: "<<"the user '"<<text2<<"' could not be found!"<<endl;
		}
	if(check_post_id==0){
		cout<<"Err: "<<text2<<"'s post could not be found!"<<endl;
		file_o<<"Err: "<<text2<<"'s post could not be found!"<<endl;
	}
}

void List::BlockUser(ifstream & file_i,ofstream & file_o){
	int check_username1=0,check_username2=0;
	string text,text1,text2;
	getline(file_i,text1,' ');
	getline(file_i,text2);

	struct node *current;
	current=head;
	while(current!=NULL){
		if(text1==current->user){
			for(int i=0 ;i<100 ;i++){
				if(current->blocked[i].compare(text2)==0){
				cout<<"Err: the user '"<<current->user<<"' has already blocked '"<<text2<<"'"<<endl;
				file_o<<"Err: the user '"<<current->user<<"' has already blocked '"<<text2<<"'"<<endl;
				return;
				}
			}
		}

	current=current->next;
	}

	current = head;
	while(current!=NULL){                    		  					// while for visit all node..
		if(text1==current->user){											// checking user ..
			check_username1=1;
		}
		if(text2==current->user){											// checking user ..
		check_username2=1;
		}

		current=current->next;
	}

	if(check_username1==1 && check_username2==1){
		current=head;
		struct node *current1;
		current1=head;
		while(current!=NULL){
			if(text1==current->user){
				for(int i=0;i<100 ;i++){
					if(current->blocked[i].compare("")==0){
						current->blocked[i]=text2;
						current->blocked_count++;
						cout<<current->user<<" has blocked "<<current->blocked[i]<<endl;
						file_o<<current->user<<" has blocked "<<current->blocked[i]<<endl;
						for(int k=0;k<100;k++){
							for(int l=0 ;l<100 ;l++){
								if(current->post[k].liked[l].compare(text2)==0){
									current->post[k].liked[l]="NULL";
									current->post[k].like_count--;
								}
							}
						}
						while(current1!=NULL){
							if(text2==current1->user){
								for(int j=0; j<100 ;j++){
									if(current1->followeds[j]==text1){
									current1->followeds[j]="NULL";
									current1->followed_count--;
									}
								}
							}

							current1=current1->next;
						}
						return;
					}
				}
			}
			current=current->next;
		}
	}
	if(check_username1==0){
		cout<<"Err: the user '"<<text1<<"' could not be found!"<<endl;
		file_o<<"Err: the user '"<<text1<<"' could not be found!"<<endl;
	}
	if(check_username2==0){
		cout<<"Err: the user '"<<text2<<"' could not be found!"<<endl;
		file_o<<"Err: the user '"<<text2<<"' could not be found!"<<endl;
	}
}

void List::UnfollowUser(ifstream & file_i,ofstream & file_o){
	string text1,text2;
	int check_username1=0,check_username2=0,check_followed=0;
	getline(file_i,text1,' ');
	getline(file_i,text2);
	struct node *current;
	current=head;
	while(current!=NULL){                    		  					// while for visit all node..
		if(text1==current->user){										// checking user ..
			check_username1=1;
			for(int i=0 ;i<100; i++){
				if(current->followeds[i].compare(text2)==0){
				current->followeds[i]="NULL";
				current->followed_count--;
				check_followed=1;
				cout<<text2<<" has been unfollowed by "<<current->user<<endl;
				file_o<<text2<<" has been unfollowed by "<<current->user<<endl;
				}
			}
		}
		if(text2==current->user)											// checking user ..
			check_username2=1;

		current=current->next;
	}

	if(check_followed==0){
		cout<<"Err: "<<text2<<" has already been unfollowed by you! You cannot unfollow again."<<endl;
		file_o<<"Err: "<<text2<<" has already been unfollowed by you! You cannot unfollow again."<<endl;
	}
	if(check_username1==0){
		cout<<"Err: the user '"<<text1<<"' could not be found!"<<endl;
		file_o<<"Err: the user '"<<text1<<"' could not be found!"<<endl;
	}
	if(check_username2==0){
		cout<<"Err: the user '"<<text2<<"' could not be found!"<<endl;
		file_o<<"Err: the user '"<<text2<<"' could not be found!"<<endl;
	}
}


int main(){

	string text;
	List list;
	ifstream file_i;
	ofstream file_o;
	file_i.open("input.txt");
	file_o.open("out.txt");
	while(file_i.eof()!=1){
	getline(file_i,text,' ');
	if(text=="AddUser"){
		list.AddUser(file_i,file_o);
	}
	else if(text=="FollowUser"){
		list.FollowUser(file_i,file_o);
	}
	else if(text=="AddPost"){
		list.AddPost(file_i,file_o);
	}
	else if(text=="LikePost"){
		list.LikePost(file_i,file_o);
	}
	else if(text=="ViewUser"){
		list.ViewUser(file_i,file_o);
	}
	else if(text=="Repost"){
		list.Repost(file_i,file_o);
	}
	else if(text=="BlockUser"){
		list.BlockUser(file_i,file_o);
	}
	else if(text=="UnfollowUser"){
		list.UnfollowUser(file_i,file_o);
	}
	}
	
	cin>>text;
	return 0;
}
