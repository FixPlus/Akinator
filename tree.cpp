#include "tree.h"

	//******************BEGIN NODE CLASS***************************

	//CONSTRUCTORS
	
Node::Node(Node* _parent, Node* _left, Node* _right,std::string _data){
	data = _data;
	left = _left;
	right = _right;
	parent = _parent;
}
	
Node::Node() : parent(NULL), left(NULL), right(NULL){
}
	
Node::~Node(){
	
}
	
	
	//FUNCTIONS
	
void Node::disconnect(Node* node){
	if(!node) return;
	if(node == left)
		left = NULL;
	else
		if(node == right)
			right = NULL;
}
	
	
	
	//getters
	
Node* Node::getLeft(){
	return left;
}
	
Node* Node::getRight(){
	return right;
}
	
Node* Node::getParent(){
	return parent;
}
	
std::string Node::getData(){
	return data;
}
	
	//setters
	
void Node::setLeft(Node* node){
	left = node;
}
	
void Node::setRight(Node* node){
	right = node;
}
	
void Node::setParent(Node* node){
	parent = node;
}
	
void Node::setData(std::string string){
	data = string;
}

	//******************END NODE CLASS************************
	//*****************BEGIN TREE CLASS***********************

	
	//CONSTRUCTORS
	
Tree::Tree(){
	head = new Node(NULL, NULL , NULL, "Tree");
}
Tree::~Tree(){
	clearBranch(head);
}
	
	//FUNCTIONS
	
void Tree::print(){
	//TODO
}
	
void Tree::clearBranch(Node* root){
	if(!root) return;
	if(root->getParent())
		root->getParent()->disconnect(root);
	
	clearBranch(root->getRight());
	clearBranch(root->getLeft());
	
	delete root;
}
	
int Tree::saveToFile(const char* filename){
	FILE* file = fopen(filename, "w");
	
	if(!file)
		return T_FILEOPEN_FAILED;
	
	saveNodeData(file, head);
	
	fclose(file);
	
	return T_SUCCESS;
}

#define T_LOAD_V2

#ifdef T_LOAD_V2 //Txt with braces
int Tree::loadFromFile(const char* filename){
	FILE* file = fopen(filename,"r");
	
	if(!file)
		return T_FILEOPEN_FAILED;
	
	struct stat st = {};
	stat(filename,&st);

	
	char* buf = new char[st.st_size+1];
	
	fgets(buf, st.st_size, file);
	fclose(file);
	
	char* ptr = buf;
	
	if(*ptr != '{')
		return T_INVALID_FILE;
	
	for(;ptr - buf < st.st_size;ptr++)
	if(*ptr == ' ' && (isBrace(*(ptr-1)) || isBrace(*(ptr+1))))
		*ptr = '\0';
	
	ptr = buf;
	Node* reserveHead = head;
	head = new Node();
	Node* temp = head;
	
	ptr += strlen(ptr) + 1;
	
	temp->setData(ptr);
	
	
	while(true){
		ptr += strlen(ptr) + 1;
		if(*ptr == '{'){
			ptr += strlen(ptr) + 1;
			Node* node = new Node(temp, NULL, NULL, ptr);
			if(!temp->getRight())
				temp->setRight(node);
			else
				if(!temp->getLeft())
					temp->setLeft(node);
				else{
					clearBranch(head);
					head = reserveHead;
					return T_INVALID_FILE;
				}
			temp = node;
		}
		else
			if(*ptr == '}'){
				temp = temp->getParent();
				if(!temp)
					break;
			}
			else{
				clearBranch(head);
				head = reserveHead;
				return T_INVALID_FILE;
			}					
	}
	
	clearBranch(reserveHead);
	
	delete[] buf;
	return T_SUCCESS;
}
#endif

#ifdef T_LOAD_V3 //Binary
int Tree::loadFromFile(const char* filename){
	//TODO
}	
#endif

int Tree::isBrace(char c){
	if(c == '}' || c == '{')
		return 1;
	else
		return 0;
}

#define T_SAVE_V1

#ifdef T_SAVE_V1 //Txt with braces	
	void Tree::saveNodeData(FILE* file, Node* node){
			
			if(!node) return;
			
			fprintf(file,"%s","{ ");
			fprintf(file,"%s ", node->getData().c_str());

			saveNodeData(file, node->getRight());
			saveNodeData(file, node->getLeft());
			
			fprintf(file,"%s","} ");			
	}
#endif

#ifdef T_SAVE_V2 //Binary
	void Tree::saveNodeData(FILE* file, Node* node){
		//TODO
		
	}
#endif

	//getters
	
Node* Tree::getHead(){
	return head;
}
		
	//setters
	
void Tree::setHead(Node* node){
	head = node;
}
	

	//************************END TREE CLASS**************************