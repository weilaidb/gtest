//#include<iostream>
//using namespace std;
//#include<gtest/gtest.h>
//int Abs(int x)
//{
//return x > 0 ? x : -x;
//}

//#if 0
//TEST(IsAbsTest,HandlerTrueReturn)
//{
//ASSERT_TRUE(Abs(1) == 1) << "Abs(1)=1"; //ASSERT_TRUE期待结果是true,operator<<输出一些自定义的信息
//ASSERT_TRUE(Abs(-1) == 1) << "Abs(-1)=1";
//ASSERT_FALSE(Abs(-2) == -2); //期待结果是false
//ASSERT_EQ(Abs(1),Abs(-1));
//ASSERT_NE(Abs(-1),0);
//ASSERT_LT(Abs(-1),2);
//ASSERT_GT(Abs(-1),0);
//ASSERT_LE(Abs(-1),2);
//ASSERT_GE(Abs(-1),0);
//}

//#endif


#include<iostream>
using namespace std;

//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <sys/types.h>
//#include <sys/time.h>
//#include <sys/fcntl.h>
//#include <assert.h>


#include <gtest/gtest.h>
#include <pthread.h>

struct LinkNode
{
int _data;
LinkNode *_next;
LinkNode(const int& data)
:_data(data)
,_next(NULL)
{}
};

class Link
{
public:
Link()
:pHead(new LinkNode(0))
{}
void PushBack(const int& data)
{
if(pHead == NULL)
return ;
LinkNode *newNode=new LinkNode(data);
if(pHead->_next == NULL){ //第一次插入结点
pHead->_next=newNode;
}
else{ //找到最后一个结点直接尾插
LinkNode *cur=pHead->_next;
while(cur->_next){
cur=cur->_next;
}
cur->_next=newNode;
}
}

void PopBack()
{
if(pHead == NULL)
return ;
LinkNode *cur=pHead;
LinkNode *prev=NULL;
while(cur->_next)
{
prev=cur;
cur=cur->_next;
}
prev->_next=NULL;
delete cur;
}

LinkNode *FindNode(const int& data)
{
if(pHead == NULL)
return NULL;
LinkNode *cur=pHead->_next;
while(cur)
{
if(cur->_data == data)
return cur;
cur=cur->_next;
}
return NULL;
}

bool Delete(int data)
{
LinkNode *pos=FindNode(data);
if(pos == NULL)
return false;
LinkNode *cur=pHead->_next;
while(cur->_next != pos)
{
cur=cur->_next;
}
cur->_next=pos->_next;
delete pos;
return true;
}

void Destroy()
{
if(pHead == NULL)
return;
LinkNode *cur=pHead->_next;
while(cur)
{
LinkNode *del=cur;
cur=cur->_next;
delete del;
del=NULL;
}
delete pHead; //删除头结点
}
LinkNode *pHead;
};

class TestLink:public testing::Test
{
public:
virtual void SetUp()
{
cout<<"SetUp"<<endl;
for(int i=1;i<=5;i++){
link.PushBack(i);
}
}
virtual void TearDown()
{
cout<<"TearDown"<<endl;
link.Destroy();
}
Link link;
};

TEST_F(TestLink,PushBack)
{
ASSERT_FALSE(link.pHead == NULL);
link.PushBack(9);
LinkNode *res=link.FindNode(9);
ASSERT_FALSE(res == NULL);
}

TEST_F(TestLink,PopBack)
{
for(int i=1;i<=5;i++){
link.PopBack();
}
}

TEST_F(TestLink,FindNode)
{
ASSERT_TRUE(link.FindNode(3));
ASSERT_TRUE(link.FindNode(2));
ASSERT_TRUE(link.FindNode(4));
ASSERT_TRUE(link.FindNode(5));
ASSERT_TRUE(link.FindNode(1));
ASSERT_FALSE(link.FindNode(7));
}

TEST_F(TestLink,Delete)
{
ASSERT_FALSE(link.pHead == NULL);
ASSERT_TRUE(link.Delete(3) == true);
ASSERT_TRUE(link.Delete(9) == false);
}
int main(int argc,char *argv[])
{
testing::InitGoogleTest(&argc,argv);
return RUN_ALL_TESTS();
}

//int main(int argc, char **argv)
//{
//    printf("hello world\n");
//    return 0;
//}



