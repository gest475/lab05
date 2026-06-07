#include <gtest/gtest.h>
#include <stdexcept>
#include "Account.h"
#include "Transaction.h"

TEST(TransactionTest, SameAccountThrows) {
    Account acc(1, 1000);
    Transaction t;
    EXPECT_THROW(t.Make(acc, acc, 500), std::logic_error);
}

TEST(TransactionTest, NegativeSumThrows) {
    Account from(1, 1000), to(2, 500);
    Transaction t;
    EXPECT_THROW(t.Make(from, to, -50), std::invalid_argument);
}

TEST(TransactionTest, SumTooSmallThrows) {
    Account from(1, 1000), to(2, 500);
    Transaction t;
    EXPECT_THROW(t.Make(from, to, 50), std::logic_error);
}

TEST(TransactionTest, FeeTooHighReturnsFalse) {
    Account from(1, 1000), to(2, 500);
    Transaction t;
    t.set_fee(60);
    EXPECT_FALSE(t.Make(from, to, 100));
}

TEST(TransactionTest, SuccessfulTransfer) {
    Account from(1, 1000), to(2, 500);
    Transaction t;
    t.set_fee(1);
    EXPECT_TRUE(t.Make(from, to, 200));
    EXPECT_EQ(from.GetBalance(), 799);
    EXPECT_EQ(to.GetBalance(), 700);
}
