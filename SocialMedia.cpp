#include<bits/stdc++.h>
using namespace std;



class User{
private:
	int id;
	string name;
	set<int>following;

public:
	User(int id,string name):id(id),name(name){};

	int getUserId(){return id;}

	string getUserName(){return name;}

	void addFollower(int followedUserId){
		if(followedUserId!=id)
			following.insert(followedUserId);
	}

	void removeFollower(int followedUserId){
		if(this->isFollowing(followedUserId)){
			following.erase(followedUserId);
		}
	}

	bool isFollowing(int userId){
		if(following.find(userId)!=following.end())
			return true;
		return false;
	}
};

class Post{
private:
	int postId;
	string content;
	int postBy;
	string createdAt;
public:
	Post(int postId,string content,int postBy,string createdAt):postId(postId),content(content),postBy(postBy),createdAt(createdAt){};

	int getPostId(){return postId;}

	string getContent(){return content;}

	int getPostBy(){return postBy;}
};



class SocialMedia{
private:
	int postCounter=0;
	map<int,User*>users;
	map<int,Post*>posts;

public:

	void registerUser(int id,string name){
		User *newUser=new User(id,name);
		users[id]=newUser;
	}


	void post(int userId,string content){
		if(users.find(userId)==users.end()){
			cout<<"User Not Registered "<<endl;
			return;
		}
		Post *newPost=new Post(postCounter,content,userId,"time");
		posts[postCounter]=newPost;
		postCounter++;
	}

	void follow(User* curUser,User *toBeFollow){
		if(users.find(toBeFollow->getUserId())==users.end()){
			cout<<"Can't Follow User as it doesn't exist "<<endl;
			return;
		}
		curUser->addFollower(toBeFollow->getUserId());
	}

	void unfollow(User* curUser,User *toBeUnFollow){
		if(users.find(toBeUnFollow->getUserId())==users.end()){
			cout<<"Can't Follow User as it doesn't exist "<<endl;
			return;
		}
		curUser->removeFollower(toBeUnFollow->getUserId());
	}


	vector<Post*>getRecentPosts(User* curUser){
		vector<Post*>userRelatedPosts;
		for(auto &post:posts){
			if(curUser->isFollowing(post.second->getPostBy())|| curUser->getUserId() == post.second->getPostBy()){
				userRelatedPosts.push_back(post.second);
			}
		}

		reverse(userRelatedPosts.begin(), userRelatedPosts.end());
		return userRelatedPosts;
	}
};



int main(){

}