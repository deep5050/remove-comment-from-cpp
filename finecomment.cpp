#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void slash_slash(string &buff, int &i)
{
  while (buff[i] != '\n') // skip upto return
  {
    i++;
  }
 //if(buff[i]=='\n') i++; // '\n' skip
}

void string_found(string &buff, string &out_buff,int &i)
{
  out_buff.push_back(buff[i]);
  i++;
  while (buff[i] != '"') //write anything including // and */
  {
    out_buff.push_back(buff[i]); // write upto second "
    i++;
}
out_buff.push_back(buff[i]); // write last "
}

void full_comment(string & buff,  int &i)
{
  i++;
  while (1)
  {
    if (buff[i] == '*' && buff[i + 1] == '/') // full comment ends here
      break;
    i++;
  }
  i++; // skip the last /
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "please try again with an input file name--" << endl;
    return -1;
  }

  int size;
  string buff;
  string out_buff;
  fstream myfile(argv[1], ios::in);
  ofstream outfile("nocomments.cpp");
  if (myfile.fail())
  {
    cout << "send correct file !!" << endl;
    return -1;
  }

  int i = 0;
  char c;
  while (1)
  {
    myfile.get(c); // read character by character
    if (myfile.eof())
      break;
    buff.push_back(c); // append to string
  }

  size = buff.length();

  for (i = 0; i <= size; i++)
  {

    if (buff[i] == '/' && buff[i + 1] == '/') // line comment starts here
    {
      slash_slash(buff, i);
    }

    if (buff[i] == '"') // string start
    {
      string_found(buff,out_buff,i);
      }
      
    

    else if (buff[i] == '/' && buff[i + 1] == '*') // full comment starts here
    {
      full_comment(buff, i);
    }

    else // normal syntax write
    {
      out_buff.push_back(buff[i]);
    }
  }
  outfile << out_buff; // write to file
  cout << "done!" << endl;
  return 0;
}