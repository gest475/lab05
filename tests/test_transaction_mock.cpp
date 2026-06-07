#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"
#include "Transaction.h"

class MockAccount : public Account {
public:
    MockAccount(int id, int balance) : Account(id, balance) {}
    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

class TestableTransaction : public Transaction {
public:
    MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

TEST(TransactionMockTest, SaveToDataBaseIsCalled) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    TestableTransaction t;
    t.set_fee(1);

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(from, GetBalance()).WillRepeatedly(testing::Return(1000));
    EXPECT_CALL(from, ChangeBalance(testing::_)).Times(1);
    EXPECT_CALL(to, ChangeBalance(testing::_)).Times(1);
    EXPECT_CALL(t, SaveToDataBase(testing::_, testing::_, 200)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    EXPECT_TRUE(t.Make(from, to, 200));
}
