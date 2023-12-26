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

TEST(TQueue, fresh_queue_is_empty)
{
    TQueue<int> queue(1);
    EXPECT_EQ(0, queue.Size());
    EXPECT_EQ(true, queue.IsEmpty());
}

TEST(TQueue, drained_queue_is_empty)
{
    TQueue<int> queue(1);
    queue.Put(1);
    queue.Poll();
    
    EXPECT_EQ(0, queue.Size());
    EXPECT_EQ(true, queue.IsEmpty());
}

TEST(TQueue, can_copy_queue)
{
    TQueue<int> queue(3);
    queue.Put(1);
    queue.Put(2);
    queue.Put(3);

    EXPECT_NO_THROW(TQueue<int> copied = queue);
}

TEST(TQueue, copied_queue_has_valid_data)
{
    TQueue<int> queue(3);
    queue.Put(1);
    queue.Put(2);
    queue.Put(3);

    TQueue<int> copied = queue;
    
    EXPECT_EQ(queue.Size(), copied.Size());

    while (!queue.IsEmpty())
    {
        EXPECT_EQ(queue.Poll(), copied.Poll());
    }
}

TEST(TQueue, can_assign_queue)
{
    TQueue<int> queue(3);
    queue.Put(1);
    queue.Put(2);
    queue.Put(3);

    TQueue<int> assigned;

    EXPECT_NO_THROW(assigned = queue);
}

TEST(TQueue, assigned_queue_has_valid_data)
{
    TQueue<int> queue(3);
    queue.Put(1);
    queue.Put(2);
    queue.Put(3);

    TQueue<int> assigned;
    assigned = queue;
    
    EXPECT_EQ(queue.Size(), assigned.Size());

    while (!assigned.IsEmpty())
    {
        EXPECT_EQ(queue.Poll(), assigned.Poll());
    }
}