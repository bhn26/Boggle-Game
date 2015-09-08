#include <vector>
#include <string>
#include <iostream>
#include "boggleutil.h"

int
main(int argc, char* argv[])
{
  std::vector<std::string> test;
  /*
  test.push_back("test1");
  test.push_back("test2");
  test.push_back("test3");
  test.push_back("test4");
  test.push_back("test5");
  test.push_back("test6");
  test.push_back("test7");
  test.push_back("test8");
  test.push_back("test9");
  test.push_back("test10");
  test.push_back("test11");
  test.push_back("test12");
  test.push_back("test13");
  test.push_back("test14");
  test.push_back("test15");
  test.push_back("test16");
  test.push_back("test17");
  test.push_back("test18");
  test.push_back("test19");
  test.push_back("test20");
  test.push_back("test21");
  test.push_back("test22");
  test.push_back("test23");
  test.push_back("test24");
  test.push_back("test25");
  test.push_back("test26");
  test.push_back("test27");
  test.push_back("test28");
  test.push_back("test29");
  test.push_back("test30");
  test.push_back("test31");
  */

  TST t;
  /*
  t.insert("call");
    t.insert("me");
      t.insert("how");
        t.insert("mind");
	  t.insert("not");
	    t.insert("no");
	      t.insert("money");
	        t.insert("milk");
		  t.insert("note");
      t.insert("opt");
  */
  //BoggleUtil::insertWords(test, 0, test.size() - 1, t);

  t.insert("a");
  t.insert("z");

  std::cout << t.root->end << std::endl;

  std::cout << t.find("a").first << std::endl;
  std::cout << t.find("a").second << std::endl;

  //std::vector<int> array ({0,1,1,1,0,-1,-1,-1});
  //std::cout << array.at(8) << std::endl;
}
