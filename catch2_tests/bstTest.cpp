#include "catch.hpp"
#include "../bst.h"

#include <sstream>
#include <string>
using namespace std;

template<typename T>
string to_string(T const& t) {
    ostringstream oss;
    oss << t;
    return oss.str();
}

TEST_CASE( "operator<<", "[bst]") {

    bst<int> tree;

    SECTION( "Tree from ASD1 slides" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);
        REQUIRE( to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))" );
    }

    SECTION( "Empty tree" ) {
        REQUIRE( to_string(tree) == "" );
    }
}

TEST_CASE( "insert", "[bst]") {

    bst<int> tree;

    SECTION( "Insert 42" ) {
        tree.insert(42);
        REQUIRE( to_string(tree) == "42" );
    }

    SECTION( "Insert smaller to the left" ) {
        tree.insert(3);
        tree.insert(2);
        REQUIRE( to_string(tree) == "3(2,.)" );
    }

    SECTION( "Insert larger to the right" ) {
        tree.insert(3);
        tree.insert(4);
        REQUIRE( to_string(tree) == "3(.,4)" );
    }

    SECTION( "Insert twice has no effect" ) {
        tree.insert(3);
        tree.insert(4);
        tree.insert(4);
        REQUIRE( to_string(tree) == "3(.,4)" );
    }
}

TEST_CASE("Display_indented", "[bst]") {
    bst<int> tree;

    SECTION( "Empty tree" ) {
      ostringstream oss;
      tree.display_indented(oss);
      REQUIRE(  oss.str() == "" );
    }

   SECTION( "Tree with two node" ) {
      for(int i : { 8, 4})
         tree.insert(i);

      ostringstream oss;
      tree.display_indented(oss);
      REQUIRE(  oss.str() == "8\n"
                             "|_ 4\n"
                             "|_ .\n" );
   }

    SECTION( "Tree from ASD1 slides" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);

        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE( oss.str() == "8\n"
                              "|_ 4\n"
                              "|  |_ 1\n"
                              "|  |  |_ .\n"
                              "|  |  |_ 2\n"
                              "|  |     |_ .\n"
                              "|  |     |_ 3\n"
                              "|  |_ 6\n"
                              "|     |_ 5\n"
                              "|     |_ 7\n"
                              "|_ 11\n"
                              "   |_ 10\n"
                              "   |_ 12\n" );
    }
}

TEST_CASE("Visit in order", "[bst]" ){
   bst<int> tree;
   bst<char> charTree;
   string os;
   SECTION( "Empty tree" ) {
      tree.visit_in_order([&os](int key){ os += to_string(key) + " "; });
      REQUIRE(  os == "" );
   }

   SECTION( "Unsorted tree" ) {
      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 9, 12})
         tree.insert(i);
      tree.visit_in_order([&os](int key){ os += to_string(key) + " " ; });
      REQUIRE(  os == "1 2 3 4 5 6 7 8 9 10 11 12 " );
   }

   SECTION( "Tree contains char" ) {
      for (char i : {'b', 'a', 'c', 'o', 'n'})
         charTree.insert(i);
      charTree.visit_in_order([&os](char key){ os += to_string(key) + " " ; });
      REQUIRE(  os == "a b c n o " );
   }
}

TEST_CASE("Copy constructor", "[bst]") {
    bst<int> tree;
	SECTION( "Empty copy" ) {
		bst<int> tree2(tree);
		REQUIRE( to_string(tree2) == "" );
	}
	
    SECTION( "Filled copy" ) {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);

		bst<int> tree3(tree);
		REQUIRE( to_string(tree3) == to_string(tree) );
    }
}

TEST_CASE("Operator=", "[bst]") {
	SECTION( "Pre-empty empty assign" ) {
		bst<int> tree;
		bst<int> tree2 = tree;
		REQUIRE( to_string(tree2) == "" );
	}
	
	SECTION( "Pre-empty filled assign" ) {
		bst<int> tree;

		for( int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 } )
            tree.insert(i);

		bst<int> tree3 = tree;

		REQUIRE( to_string(tree3) == to_string(tree) );
	}
	
	SECTION( "Pre-filled empty assign" ) {
		bst<int> emptyTree;
		bst<int> filledTree;

		for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            filledTree.insert(i);

		filledTree = emptyTree;

		REQUIRE( to_string(filledTree) == "" );
	}

	SECTION( "Pre-filled filled assign smaller" ) {
		bst<int> smallTree;
		bst<int> bigTree;

		for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            bigTree.insert(i);
		for(int i : { 8, 4, 1, 2, 3, 6, 5 })
            smallTree.insert(i);

		bigTree = smallTree;

		REQUIRE( to_string(bigTree) == to_string(smallTree) );
	}

	SECTION( "Pre-filled filled assign bigger" ) {
		bst<int> smallTree;
		bst<int> bigTree;

		for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            bigTree.insert(i);
		for(int i : { 8, 4, 1, 2, 3, 6, 5 })
            smallTree.insert(i);

		smallTree = bigTree;

		REQUIRE( to_string(bigTree) == to_string(smallTree) );
	}
}

TEST_CASE("contains", "[bst]") {
	bst<int> tree;

   SECTION( "Empty Tree" ) {

         REQUIRE( !tree.contains(5) );
   }

   for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
      tree.insert(i);

	SECTION( "contains" ) {


		for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            REQUIRE( tree.contains(i) );
	}

	SECTION( "does not contain" ) {
		for(int i : { 9, 13, -1 })
            REQUIRE( !tree.contains(i) );
	}
}

TEST_CASE("Linearize", "[bst]") {
   bst<int> tree;

   SECTION( "Empty tree" ) {
      tree.linearize();
      REQUIRE( to_string(tree) == "" );
   }

   SECTION("Normal tree") {
      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      tree.linearize();
      REQUIRE( to_string(tree) == "1(.,2(.,3(.,4(.,5(.,6(.,7(.,8(.,10(.,11(.,12))))))))))" );
   }

   SECTION("Tree already linearized") {
      for (int i : {12,11,10,9,8})
         tree.insert(i);
      tree.linearize();
      REQUIRE(to_string(tree) == "8(.,9(.,10(.,11(.,12))))");
   }

}

TEST_CASE("Balance", "[bst]") {
   bst<int> tree;

   SECTION( "Empty tree" ) {
      tree.balance();
      REQUIRE( to_string(tree) == "" );
   }

   SECTION("Unbalanced Tree") {
      for (int i : {1,2,3,4,5,6,7,8})
         tree.insert(i);
      tree.balance();
      REQUIRE( to_string(tree) == "4(2(1,3),6(5,7(.,8)))");

   }

   SECTION("Unbalanced Tree with elements inserted backwards") {
      for (int i : {8,7,6,5,4,3,2,1})
         tree.insert(i);
      tree.balance();
      REQUIRE( to_string(tree) == "4(2(1,3),6(5,7(.,8)))");

   }

   SECTION("Unbalanced Tree with randomly inserted elements") {
      for (int i : {1,7,4,3,8,2,6,5})
         tree.insert(i);
      tree.balance();
      REQUIRE( to_string(tree) == "4(2(1,3),6(5,7(.,8)))");

   }
}

TEST_CASE("min()", "[bst]") {
    bst<int> tree;

    SECTION("Empty tree") {
        REQUIRE_THROWS_AS(tree.min(), std::exception);
    }

    SECTION("Tree of one element") {
        tree.insert(8);
        REQUIRE(to_string(tree.min()) == "8");
    }

    SECTION("Tree with no left branch") {
        for (int i : {8, 11, 10, 12})
            tree.insert(i);
        REQUIRE(to_string(tree.min()) == "8");
    }

    SECTION("Tree with no right branch") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7})
            tree.insert(i);
        REQUIRE(to_string(tree.min()) == "1");
    }

    SECTION("Tree of many elements") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        REQUIRE(to_string(tree.min()) == "1");
    }
}

TEST_CASE("max()", "[bst]") {
    bst<int> tree;

    SECTION("Empty tree") {
        REQUIRE_THROWS_AS(tree.max(), std::exception);
    }

    SECTION("Tree of one element") {
        tree.insert(8);
        REQUIRE(to_string(tree.max()) == "8");
    }

    SECTION("Tree with no left branch") {
        for (int i : {8, 11, 10, 12})
            tree.insert(i);
        REQUIRE(to_string(tree.max()) == "12");
    }

    SECTION("Tree with no right branch") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7})
            tree.insert(i);
        REQUIRE(to_string(tree.max()) == "8");
    }

    SECTION("Tree of many elements") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        REQUIRE(to_string(tree.max()) == "12");
    }
}

TEST_CASE("erase_min()", "[bst]") {
    bst<int> tree;

    SECTION("Empty tree") {
        REQUIRE_THROWS_AS(tree.erase_min(), std::exception);
    }

    SECTION("Tree of one element") {
        tree.insert(8);
        tree.erase_min();
        REQUIRE(to_string(tree) == "");
    }

    SECTION("Tree with no left branch") {
        for (int i : {8, 11, 10, 12})
            tree.insert(i);
        tree.erase_min();
        REQUIRE(to_string(tree) == "11(10,12)");
    }

    SECTION("Tree with no right branch") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7})
            tree.insert(i);
        tree.erase_min();
        REQUIRE(to_string(tree) == "8(4(2(.,3),6(5,7)),.)");
    }

    SECTION("Tree of many elements") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        tree.erase_min();
        REQUIRE(to_string(tree) == "8(4(2(.,3),6(5,7)),11(10,12))");
    }
}

TEST_CASE("erase_max()", "[bst]") {
    bst<int> tree;

    SECTION("Empty tree") {
        REQUIRE_THROWS_AS(tree.erase_max(), std::exception);
    }

    SECTION("Tree of one element") {
        tree.insert(8);
        tree.erase_max();
        REQUIRE(to_string(tree) == "");
    }

    SECTION("Tree with no left branch") {
        for (int i : {8, 11, 10, 12})
            tree.insert(i);
        tree.erase_max();
        REQUIRE(to_string(tree) == "8(.,11(10,.))");
    }

    SECTION("Tree with no right branch") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7})
            tree.insert(i);
        tree.erase_max();
        REQUIRE(to_string(tree) == "4(1(.,2(.,3)),6(5,7))");
    }

    SECTION("Tree of many elements") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        tree.erase_max();
        REQUIRE(to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,.))");
    }
}

TEST_CASE("erase(Key const& k)", "[bst]") {
    bst<int> tree;
    int key;

    SECTION("Empty tree") {
        key = 3;
        REQUIRE(to_string(tree) == "");
    }

    SECTION("Tree of one element, contains searched key") {
        tree.insert(8);
        key = 8;
        tree.erase(key);
        REQUIRE(to_string(tree) == "");
    }

    SECTION("Tree of one element, NO searched key") {
        tree.insert(8);
        key = 4;
        tree.erase(key);
        REQUIRE(to_string(tree) == "8");
    }

    SECTION("Node with no left branch, contains searched key") {
        for (int i : {8, 4, 6 ,11, 10}) // 8(4(.,6),11(10,.))
            tree.insert(i);
        key = 4;
        tree.erase(key);
        REQUIRE(to_string(tree) == "8(6,11(10,.))");
    }

    SECTION("Node with no right branch, contains searched key") {
        for (int i : {8, 4, 6 ,11, 10}) // 8(4(.,6),11(10,.))
            tree.insert(i);
        key = 11;
        tree.erase(key);
        REQUIRE(to_string(tree) == "8(4(.,6),10)");
    }

    SECTION("Node with both right and left branch, contains searched key") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        key = 4;
        tree.erase(key);
        REQUIRE(to_string(tree) == "8(5(1(.,2(.,3)),6(.,7)),11(10,12))");
    }

    SECTION("Node with both right and left branch, NO searched key") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        key = 9;
        tree.erase(key);
        REQUIRE(to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))");
    }
}