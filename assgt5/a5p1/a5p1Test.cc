#include "a5p1.h"
#include "gtest/gtest.h"
TEST(DogPub, ExpectDogToSpeakItsName) {
	Dog bolt{"Bolt"};
	EXPECT_EQ(bolt.speak(), "    Dog Bolt says \"woof\".");
}
TEST(SheepPub, ExpectSheepToSpeakItsName) {
	Sheep shaun{"Shaun"};
	EXPECT_EQ(shaun.speak(), "    Sheep Shaun says \"baaa\".");
}
TEST(FlockPub, FlockWithNoSheep) {
    Flock spot{"Spot"};
    std::string expected_output = "The flock of 0 sheep speaks!\n"
                             "    Dog Spot says \"woof\".\n";
    EXPECT_EQ(spot.soundOff(), expected_output);
}
TEST(FlockPub, FlockWithSheep) {
    Flock f{"Dog"};
    f.addSheep("Sheep1");
    f.addSheep("Sheep2");
    EXPECT_EQ(f.soundOff(), "The flock of 2 sheep speaks!\n    Dog Dog says \"woof\".\n    Sheep Sheep1 says \"baaa\".\n    Sheep Sheep2 says \"baaa\".\n");
}