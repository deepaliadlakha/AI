#include<iostream>
#include<map>
#include<string>
#include<map>
#include<unordered_map>

using namespace std;


void build_dictionary()
{
	string s;
	char cur_word[140];
	int word_count = 0;
	unordered_map<string,int> dictionary;
	while(getline(cin,s))
	{
		//cout<<"entering new line"<<endl;
		int n = s.length();
		for(int i=0;i<n;i++)
		{
			//cout<<i<<endl;
			while(i<n && s[i] == ' ' && s[i] == '\t')i++;
			int j=0;
			while(i<n && s[i] != ' ' && s[i] != '\t')
			{
				if(s[i] == '.' || s[i] == '"'  || s[i] == ',' || s[i] == '!') 
				{
					i++;
				}
				else
					cur_word[j++] = s[i++];								
			}
			
			cur_word[j] = '\0';
			//printf("%s\n",cur_word);
			if (dictionary.count(string(cur_word)) <=0)
			{
				//printf("%s\n",cur_word);
				dictionary.insert(pair<string,int>(string(cur_word),word_count));
				word_count++;
				//cout<<"here";
			}
		}
	}
	cout<<word_count<<endl;	
	return ;
}


