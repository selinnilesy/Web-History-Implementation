#include <iostream>


class Tab {
    public:
        Tab();
        Tab(std::string url, int timestamp);
        Tab(const Tab &obj);

        std::string getUrl() const;
        void setUrl(std::string url);
        std::string getWebSite() const;
        int getTimestamp() const;
        void setTimestamp(int timestamp);

        friend std::ostream &operator<<(std::ostream &os, const Tab &obj);

        bool operator==(const Tab &rhs);
        bool operator<=(const Tab &rhs);

    private:
        std::string url;
        int timestamp;
};

Tab::Tab()
{

}

Tab::Tab(std::string url, int timestamp)
{
    this->url = url;
    this->timestamp = timestamp;
}

Tab::Tab(const Tab &obj)
{
    this->url = obj.url;
    this->timestamp = obj.timestamp;
}

std::string Tab::getUrl() const
{
    return url;
}

void Tab::setUrl(std::string url)
{
    this->url = url;
}

std::string Tab::getWebSite() const
{
    std::string page = this->url;
    std::string delimiter = ".";
    std::string webPage = "";
    size_t pos = 0;
    
    for (int i = 0; i < 2; i++)
    {
        pos = page.find(delimiter);
        webPage = page.substr(0, pos);
        page.erase(0, pos + delimiter.length());
    }
    return webPage;
}

int Tab::getTimestamp() const
{
    return timestamp;
}

void Tab::setTimestamp(int timestamp)
{
    this->timestamp = timestamp;
}

std::ostream &operator<<(std::ostream &os, const Tab &obj)
{
    os << "Url: " << obj.url;
    os << " Timestamp: " << obj.timestamp;
    return os;
}

bool Tab::operator==(const Tab &rhs)
{
    if (rhs.url == "")
    {
        return this->timestamp == rhs.timestamp;
    }
    else if (rhs.timestamp == -1)
    {
        return this->url == rhs.url;
    }
    return (this->url == rhs.url) && (this->timestamp == rhs.timestamp);
}

bool Tab::operator<=(const Tab &rhs)
{
    return this->timestamp <= rhs.timestamp;
}

template<class T>
class Node
{
    public:
        T element;
        Node<T> *prev;
        Node<T> *next;

        Node();
        Node(T element, Node<T> *prev, Node<T> *next);
        Node(const Node<T> &obj);

        friend std::ostream &operator<<(std::ostream &os, const Node<T> &obj)
        {
            os << obj.element;
            return os;
        }
};

template<class T>
Node<T>::Node()
{
    prev = NULL;
    next = NULL;
}

template<class T>
Node<T>::Node(T element, Node<T> *prev, Node<T> *next)
{
    this->element = element;
    this->prev = prev;
    this->next = next;
}

template<class T>
Node<T>::Node(const Node<T> &obj)
{
    this->element = obj.element;
    this->prev = obj.prev;
    this->next = obj.next;
}


template <class T>
class LinkedList
{
    public: // DO NOT CHANGE THIS PART.
        LinkedList();
        LinkedList(const LinkedList &obj);

        ~LinkedList();

        Node<T> *getFirstNode() const; //
        Node<T> *getHead() const;
        Node<T> *getTail() const;
        int getNumberOfNodes();
        bool isEmpty(); //

        void insertAtTheFront(const T &data); //
        void insertAtTheEnd(const T &data); //
        void insertAfterGivenNode(const T &data, Node<T> *prev); //

        void removeNode(Node<T> *node);
        void removeAllNodes();

        Node<T> *findNode(const T &data); //

        void printAllNodes();
        void printReversed();

        LinkedList &operator=(const LinkedList &rhs);

    private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

    private: // DO NOT CHANGE THIS PART.
        Node<T> *head;
        Node<T> *tail;
};
class WebHistory
{
    public:
        WebHistory();
        WebHistory(std::string history);
        
      
        WebHistory(std::string url, int timestamp);
        
       
        void printHistory();
        
       
        void insertInOrder(Node<Tab> *newPage);

      
        void goToPage(std::string url, int timestamp);
        
   
        void clearHistory();

     
        void clearHistory(int timestamp);

        WebHistory operator+(const WebHistory &rhs) const;

    
        int timesVisited(std::string pageName);
      
        std::string mostVisited();

    private:
        LinkedList<Tab> history;
};
WebHistory::WebHistory()
{
    // Does nothing.
}

WebHistory::WebHistory(std::string historyText)
{
    // history = url timestamp | url timestamp | url timestamp...
    // urls are string and timestamps are non-negative integers.
    std::string delimiter = " | ";

    std::string tabInfo;
    std::string url;
    std::string timestamp;
    size_t pos = 0;

    while (true)
    {
        pos = historyText.find(delimiter);

        bool breakTheLoop = (pos == std::string::npos);

        tabInfo = historyText.substr(0, pos);
        historyText.erase(0, pos + delimiter.length());

        pos = tabInfo.find(" ");
        
        url = tabInfo.substr(0, pos);
        timestamp = tabInfo.substr(pos + 1, tabInfo.length() - pos);

        Node<Tab> *newPage = new Node<Tab>(Tab(url, std::atoi(timestamp.c_str())), NULL, NULL);
        insertInOrder(newPage);

        if (breakTheLoop)
        {
            break;
        }
    }
}

void WebHistory::printHistory()
{
    std::cout << "Your web history:" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << std::endl;
    if (history.getHead()->next == history.getTail())
    {
        std::cout << "History is empty." << std::endl;
        std::cout << std::endl;
    }
    else
    {
        Node<Tab> *node = history.getFirstNode();
        
        while (node != history.getTail())
        {
            std::cout << "Page: " << node->element.getUrl() << std::endl;
            std::cout << "Last Visited: " << node->element.getTimestamp() << std::endl;
            std::cout << std::endl;
            node = node->next;
        }
    }
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << std::endl;
}

WebHistory::WebHistory(std::string url, int timestamp)
{
    if(history.getHead())
    {
    Tab data(url,timestamp);
    Node<Tab> *newnode= new Node<Tab>(data,history.getHead(),history.getTail());
    }
    
}
void WebHistory::insertInOrder(Node<Tab> *newPage)
{
    if(history.getHead()){
    Node<Tab> *temp=history.getHead()->next;
    if(temp==history.getTail()){ //history bossa
        history.getHead()->next=newPage;
        newPage->next=temp;
        temp->prev=newPage;
        newPage->prev=history.getHead();
    }
    else{
        int deger= newPage->element.getTimestamp();
        while(temp!=history.getTail()){
        if(temp->element.getTimestamp() <= deger ){
            temp->prev->next=newPage;
            newPage->next=temp;
            newPage->prev=temp->prev;
            temp->prev=newPage;
            break;}
        temp=temp->next;
        }
        if(temp==history.getTail()){
            temp->prev->next=newPage;
            newPage->prev=temp->prev;
            temp->prev=newPage;
            newPage->next=temp;
        }
    }
}
}
void WebHistory::clearHistory(int timestamp)
{
Node<Tab> *head=history.getHead();
Node<Tab> *tail=history.getTail();
if(head && tail && head->next!=tail){
    Node<Tab> *temp=head->next;
    Node<Tab> *later=NULL;
    if(head->next!=tail){
        while(temp){
            if(temp->element.getTimestamp() <= timestamp){
            temp->prev->next=history.getTail();
                later=temp->prev;
            break;}
            temp=temp->next;}
    
    if(temp->next==tail){
        delete temp;
    }
    else{
        while(temp!=tail){
        temp=temp->next;
        delete temp->prev;
        }
    }
        history.getTail()->prev=later;
}
}}

WebHistory WebHistory::operator+(const WebHistory &rhs) const
{
    WebHistory result;
    Node<Tab> *head1= history.getHead()->next;
    Node<Tab> *head2= rhs.history.getHead()->next;
    if(head1 && head2){
        while(head1!=history.getTail()){
            result.history.insertAtTheEnd(head1->element);
            head1=head1->next;
        }
        while(head2!=rhs.history.getTail()){
            Node<Tab> *temp= new Node<Tab>(head2->element,NULL,NULL);
            result.insertInOrder(temp);
            head2=head2->next;
        }
    }
    return result;
}

int WebHistory::timesVisited(std::string pageName)
{
if(history.getHead()){
    int count=0;
      Node<Tab> *temp= history.getHead()->next;
      if(temp!=history.getTail()){
       while(temp!=history.getTail()){
          if(pageName==temp->element.getWebSite()) count++;
          temp=temp->next;
      }
  }
  return count;
}
    return 0;}

std::string WebHistory::mostVisited()
{
    int timesmax=0;
    std::string page;
    if(history.getHead()){
      Node<Tab> *temp= history.getHead()->next;
      if(temp!=history.getTail()){
       while(temp!=history.getTail()){
           int i=timesVisited(temp->element.getWebSite());
           if(i > timesmax){
               timesmax=i;
               page=temp->element.getWebSite();
           }
           temp=temp->next;
}
          
      }}
    return page;
}

using namespace std;
template<class T>
LinkedList<T>::LinkedList()
{ Node<T> *dummyhead= new Node<T>;
       head=dummyhead;
       Node<T> *dummytail= new Node<T>;
       tail=dummytail;
       dummyhead->next=dummytail;
       dummytail->prev=dummyhead;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &obj)
{
    Node<T> *dummyhead= new Node<T>;
    head=dummyhead;
    Node<T> *dummytail= new Node<T>;
    tail=dummytail;
    dummyhead->next=dummytail;
    dummytail->prev=dummyhead;
    Node<T> *temp=obj.head->next;
    while(temp!=obj.tail){
        insertAtTheEnd(temp->element);
        temp=temp->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{
   removeAllNodes();
    delete head;
    head=NULL;
    delete tail;
    tail=NULL;
}

template<class T>
Node<T> * LinkedList<T>::getFirstNode() const
{
     if(head->next!=tail) return head->next;
       else return NULL;
}

template<class T>
Node<T> * LinkedList<T>::getHead() const
{
    return head;
}

template<class T>
Node<T> * LinkedList<T>::getTail() const
{
   return tail;
}

template<class T>
int LinkedList<T>::getNumberOfNodes()
{
     if(!head) return 0;
       else{
       Node<T> *temp=NULL;
           int count=0;
       if(head->next!=tail){
           for(temp=head->next ; temp; temp=temp->next){
               count++;}
           --count;
       }
       return count;}
}

template<class T>
bool LinkedList<T>::isEmpty()
{
     if(head && head->next!=tail){return 0 ;}
       else{ return 1;}
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data)
{
    
    if(head){
    Node<T> *temp=new Node<T>(data,head,head->next);
    head->next->prev=temp;
    head->next=temp;}
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data)
{
     if(tail){
       Node<T> *temp=new Node<T>(data,tail->prev,tail);
       tail->prev->next=temp;
       tail->prev=temp;}
    
    
}

template<class T>
void LinkedList<T>::insertAfterGivenNode(const T &data, Node<T> *prev)
{
    if(prev){
        if(prev==tail){
        Node<T> *temp=new Node<T>(data,prev,NULL);
        temp->prev->next=temp;
        tail=temp;}
        else{
        Node<T> *temp=new Node<T>(data,prev,prev->next);
        temp->prev->next=temp;
        temp->next->prev=temp;}
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
if(node==head){
        Node<T> *temp=head;
        temp->next->prev=NULL;
        head=temp->next;
        delete temp;
    }
else if(node==tail){
        Node<T> *temp=tail;
        temp->prev->next=NULL;
        tail=temp->prev;
        delete temp;
   }
else{
    if(head && tail){
    Node<T> *temp=head->next;
    while(temp){
        if(temp==node){
            temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
            delete temp;
            break;}
        temp=temp->next;}
    }}
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
if(head && tail){
if(head->next!=tail){
    Node<T> *temp=tail->prev->prev;
    while(temp){
        Node<T> *tobedeleted=temp->next;
        temp->next=temp->next->next;
        temp->next->prev=temp;
        delete tobedeleted;
        if(temp==head) break;
        else temp=temp->prev;
    }
}

}
}


template<class T>
Node<T> * LinkedList<T>::findNode(const T &data)
{if(head && tail){
        if(head->next!=tail){
        Node<T> *temp=head->next;
        for(; temp!=tail; temp=temp->next){
            if(temp->element==data) return temp;}
        }
    }
    return NULL;
}

template<class T>
void LinkedList<T>::printAllNodes()
{
    if(head){
        if(head->next!=tail){
        Node<T> *temp=head->next;
        while(temp!=tail){
            cout<< temp->element << endl;
            temp=temp->next;}
        }
    }
}

template<class T>
void LinkedList<T>::printReversed()
{if(head && tail){
       
        Node<T> *temp=tail->prev;
        if(temp!=head){
        while(temp!=head){
            cout<< temp->element << endl;
            temp=temp->prev;
        }}
     
    }
}

template<class T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList &rhs)
{
       removeAllNodes();
       Node<T> *temp=rhs.head->next;
       while(temp!=rhs.tail){
           insertAtTheEnd(temp->element);
           temp=temp->next;
       }
    return *this;
}


int main() {
    
    WebHistory a;
       Tab x("www.youtube.com", 1);
       Tab y("www.youtube.com/ece", 2);
       Tab z("www.youtube.com/ecece", 3);
       Node<Tab> *s= new Node<Tab>(x,NULL,NULL);
       Node<Tab> *p= new Node<Tab>(y,NULL,NULL);
       Node<Tab> *t= new Node<Tab>(z,NULL,NULL);
    
       a.insertInOrder(s);
       a.insertInOrder(p);
       a.insertInOrder(t);
    Tab h("www.youtube.com", 99);
    Node<Tab> *d= new Node<Tab>(h,NULL,NULL);
    
      
   
    a.insertInOrder(d);
    a.printHistory();
    
    return 0;
}
