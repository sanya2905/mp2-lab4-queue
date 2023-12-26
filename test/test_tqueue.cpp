#include <gtest.h>
#include "TQueue.h"

TEST(TQueue, can_create_queue)
{
    EXPECT_NO_THROW(TQueue<int> queue(8));
}

TEST(TQueue, can_put_element)
{
    TQueue<int> queue(8);
    ASSERT_NO_THROW(queue.Put(1));
    EXPECT_EQ(1, queue.Size());
}

TEST(TQueue, can_poll_element)
{
    TQueue<int> queue(8);
    ASSERT_NO_THROW(queue.Put(2));
    EXPECT_EQ(2, queue.Poll());
}

TEST(TQueue, cant_poll_from_empty_queue)
{
    TQueue<int> queue(1);
    EXPECT_ANY_THROW(queue.Poll());
}

TEST(TQueue, cant_put_to_full_queue)
{
    TQueue<int> queue(1);
    ASSERT_NO_THROW(queue.Put(1));
    EXPECT_ANY_THROW(queue.Put(2));
}