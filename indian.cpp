#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<limits.h>
#include <vector>
#include<map>
#include <algorithm>
using namespace std;

class adjList{
public:
        int index;
        bool checked;
        int finalPosition;
        vector<int> list;
        adjList(){}

         adjList(int index){
          this->index=index;
          checked=false;
        }

        int length(){
          return list.size();
        }

        void addtoList(int pos){
          list.push_back(pos);
        }

        void removefromList(int item){
          //list.erase(std::remove(list.begin(), list.end(), item), list.end());
          for( std::vector<int>::iterator iter = list.begin(); iter != list.end(); ++iter )
          {
              if( *iter == item )
                {
                    list.erase( iter );
                    //break;
                }
          }
        }
};



int find_min_edge_element(map<int,adjList>& database,int map_key){

  //if(database[0].checked && database[2].checked)  cout<<"\ncalled min_edge_element for "<<map_key<<endl;

  map<int,adjList>::iterator it;
  int min_count=INT_MAX;
  int min_index=0;

for(int element_index=0;element_index<database[map_key].list.size();element_index++)
{
    int element=database[map_key].list[element_index];
    int counter=0;
    for(it=database.begin();it!=database.end();it++)
    if(it->second.checked==false  &&  find(it->second.list.begin(),it->second.list.end(),element)!=it->second.list.end())
      {
          counter++;
      }

      //cout<<"counter for  "<<element <<" is "<<counter<<endl;
    if(counter< min_count)
    {
        min_count=counter;
        min_index=element_index;
    }

}

  return database[map_key].list[min_index];
}

void delete_from_database(map<int,adjList>& database,int value){

  map<int,adjList>::iterator it;
  for(it=database.begin();it!=database.end();it++)
  if(it->second.checked==false )
  {
        //cout<<"\nelements are : ";
      for(int i=0;i<it->second.list.size();i++)
      if(it->second.list[i]==value)
          it->second.list.erase(it->second.list.begin()+i);
   }


  /*  if(it->second.list.size()>1)
      it->second.removefromList(value);

    else if(it->second.list[0]==value)
      it->second.list.clear();
      */

}

int find_min_index(map<int,adjList>& database){



  map<int,adjList>::iterator it;
  int min_count=INT_MAX;
  int min_index=-1;


  for(it=database.begin();it!=database.end();it++)
  if(it->second.checked==false &&  it->second.length()>0  &&  it->second.length()<min_count)
  {
    min_index=it->first;
    min_count=it->second.length();
  }

  return min_index;
}


void debug_print(string keyWord,map<int,adjList>database)
{
  for(int pos=0;pos<keyWord.length();pos++)
        {

          vector<int> temp=database[pos].list;
          cout<<"adjacency list for "<<keyWord[pos]<<" is :";
          for(int i=0;i<temp.size();i++)
          cout<<temp[i]<<"\t";
          if(database[pos].checked==true)
          cout<<"checked";
          cout<<endl;

        }


}

void IMPOSSIBLE(string input){
        cout<<input<<" is impossible to generate.\n";
        exit(0);
}


int main(){
vector<string> input;
string keyWord;
map<int,adjList> database;

while(1)
{
  cin>>keyWord;
  if(keyWord=="keyword" ||  keyWord=="KEYWORD"  || keyWord=="keyWord"  )
    break;
  input.push_back(keyWord);
}

cin>>keyWord;

if(input.size()<keyWord.length())
    IMPOSSIBLE(keyWord);

for(int pos=0;pos<keyWord.length();pos++)
{
  adjList adj(pos);
  database[pos]=adj;

  for(int j=0;j<input.size();j++)
    if(input[j].find(keyWord[pos])!=std::string::npos)
        database[pos].addtoList(j);
}


for(int pos=0;pos<keyWord.length();pos++)
if(database[pos].list.size()==0)
    IMPOSSIBLE(keyWord);

//  debug_print(keyWord,database);

while(true)
{
    //find the minimum length adjacency list
    int index=find_min_index(database);
    //cout<<"Minimum length is "<<index<<" + ";
    //if(index==0)

    if(index==-1) break;      //sequence complete

    int selectedWord=find_min_edge_element(database,index);

    database[index].finalPosition=selectedWord;
    database[index].checked=true;

    delete_from_database(database,selectedWord);

    //cout<<"Selected word is "<<selectedWord<<endl;
  //  debug_print(keyWord,database);
}


  for(int pos=0;pos<keyWord.length();pos++)
    if(database[pos].checked==false)
        IMPOSSIBLE(keyWord);



cout<<"Final Selection is:\n";

for(int pos=0;pos<keyWord.length();pos++){
  int index=database[pos].finalPosition;

  cout<<input[index]<<endl;
}


/*for(int i=0;i<input.size();i++) cout<<input[i]<<endl; cout<<"keyWord is "<<keyWord<<endl;*/

  return 0;
}
