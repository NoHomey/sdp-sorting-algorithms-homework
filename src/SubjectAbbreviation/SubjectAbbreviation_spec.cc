#include "SubjectAbbreviation.h"
#include "../test/includes.h"

TEST(SubjectAbbreviation, isValid) {
    IT("returns false if the given string is null pointer");
    EXPECT_FALSE(SubjectAbbreviation::isValid(nullptr));

    IT("returns false if the given string is empty stirng");
    EXPECT_FALSE(SubjectAbbreviation::isValid(""));

    IT("returns true if the given string is from upto 12 upper case letters");
    EXPECT_TRUE(SubjectAbbreviation::isValid("SDP"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("OOP"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("FP"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("LAC"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("LA"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("AG"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("CT"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("DAA"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("MLWP"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("IESIP"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("DEAAPP"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("MMAR"));
    EXPECT_TRUE(SubjectAbbreviation::isValid("ACPP"));

    IT("returns false if the given string has more than 12 upper case letters");
    EXPECT_FALSE(SubjectAbbreviation::isValid("SDPAHDHDJSJSS"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("OOPDFKJFDFAGH"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("FDFJNDJASHFJDHFJP"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("DFSKFSDFJDSJFJSDFK"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("USJCMZMZKFKSMXMZ"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("KFKDJSLCJVFNKDJFJD"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("DDJHJSHSHAJAAAAS"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("HSKGKHSDHXBNFKDJ"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("ASJSJJJASFJSE"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("JSJSJSSJSJSSJ"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("ANYLANGYOUCAN"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("LASTONESTANDING"));
    EXPECT_FALSE(SubjectAbbreviation::isValid("ONEMOREWITHMORE"));
}

TEST(SubjectAbbreviation, getSubjectAbbreviation) {
    IT("returns the exact same subject abbreviation wich was last hashed");

    IT("returns the exact same subject abbreviation with wich was constructed if not setSubjectAbbreviation was made");
    EXPECT_STREQ(SubjectAbbreviation("SDP").getSubjectAbbreviation(), "SDP");

    EXPECT_STREQ(SubjectAbbreviation("OOP").getSubjectAbbreviation(), "OOP");

    EXPECT_STREQ(SubjectAbbreviation("FP").getSubjectAbbreviation(), "FP");

    EXPECT_STREQ(SubjectAbbreviation("LAC").getSubjectAbbreviation(), "LAC");

    EXPECT_STREQ(SubjectAbbreviation("LA").getSubjectAbbreviation(), "LA");

    EXPECT_STREQ(SubjectAbbreviation("AG").getSubjectAbbreviation(), "AG");

    EXPECT_STREQ(SubjectAbbreviation("CT").getSubjectAbbreviation(), "CT");

    EXPECT_STREQ(SubjectAbbreviation("DAA").getSubjectAbbreviation(), "DAA");

    SubjectAbbreviation object{"MLWP"};
    EXPECT_STREQ(object.getSubjectAbbreviation(), "MLWP");
    IT("returns the exact same subject abbreviation wich was last hashed, (argument of last setSubjectAbbreviation call)");
    object.setSubjectAbbreviation("IESIP");
    EXPECT_STREQ(object.getSubjectAbbreviation(), "IESIP");
    object.setSubjectAbbreviation("DEAAPP");
    EXPECT_STREQ(object.getSubjectAbbreviation(), "DEAAPP");
    object.setSubjectAbbreviation("MMAR");
    EXPECT_STREQ(object.getSubjectAbbreviation(), "MMAR");
}