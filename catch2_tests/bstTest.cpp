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

TEST_CASE("display_indented", "[bst]") {
    bst<int> tree;

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

TEST_CASE("Parcour croissant", "[bst]" ){
   bst<int> tree;

   SECTION( "Tree from ASD1 slides" ) {
      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      cout<<"Parcour de l'arbre en ordre croissant"<<endl;
      tree.visit_in_order([](int key){ cout<<key<<" "; });
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

		for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
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

   SECTION("Tree from ASD1 slides") {
      for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
         tree.insert(i);

      tree.linearize();
      ostringstream oss;
      tree.display_indented(oss);
      cout << oss.str();
   }
}
TEST_CASE("Balance", "[bst]") {
   bst<int> tree;

   SECTION("Tree from ASD1 slides") {
      for (int i : {1,2,3,4,5,6,7,8})
         tree.insert(i);
      tree.balance();
      ostringstream oss;
      tree.display_indented(oss);
      cout << oss.str();
   }
}

TEST_CASE("min()", "[bst]") {
    bst<int> tree;

    SECTION("Empty tree") {
        REQUIRE(to_string(tree.min()) == "std::exception");
    }

    SECTION("Non-Empty tree") {
        for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
            tree.insert(i);
        REQUIRE(to_string(tree.min()) == "1");
    }

}

TEST_CASE("max()", "[bst]") {


}

TEST_CASE("erase_min()", "[bst]") {

}

TEST_CASE("erase_max()", "[bst]") {

}

TEST_CASE("erase(Key const& k)", "[bst]") {

}