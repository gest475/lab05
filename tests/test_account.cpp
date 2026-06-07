#include <gtest/gtest.h>
#include <stdexcept>
#include "Account.h"

TEST(AccountTest, InitialBalance) {
    Account acc(1, 100);
    EXPECT_EQ(acc.GetBalance(), 100);
    EXPECT_EQ(acc.id(), 1);
}

TEST(AccountTest, LockUnlockChangeBalance) {
    Account acc(2, 200);
    EXPECT_THROW(acc.ChangeBalance(50), std::runtime_error);
    acc.Lock();
    acc.ChangeBalance(50);
    EXPECT_EQ(acc.GetBalance(), 250);
    acc.Unlock();
}

TEST(AccountTest, DoubleLockThrows) {
    Account acc(3, 0);
    acc.Lock();
    EXPECT_THROW(acc.Lock(), std::runtime_error);
}

TEST(AccountTest, UnlockWithoutLockWorks) {
    Account acc(4, 100);
    EXPECT_NO_THROW(acc.Unlock());
}
