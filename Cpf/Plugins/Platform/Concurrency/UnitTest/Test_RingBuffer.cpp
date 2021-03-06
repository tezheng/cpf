//////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "gmock/gmock.h"
#include "Concurrency/Collections/RingBuffer.hpp"


TEST(Concurrency, RingBuffer_Basics)
{
	using namespace CPF::Concurrency;
	Collections::RingBuffer<int32_t> ringBuffer(4);
	EXPECT_TRUE(ringBuffer.Initialize(1));

	int32_t temp;
	EXPECT_EQ(Collections::RingBuffer<int32_t>::InvalidIndex, ringBuffer.Fetch(0, temp));

	EXPECT_EQ(2, ringBuffer.Reserve(1, 2));

	EXPECT_TRUE(ringBuffer.PushBack(1, 50));
	EXPECT_TRUE(ringBuffer.PushBack(1, 51));

	EXPECT_EQ(0, ringBuffer.Fetch(0, temp));
	EXPECT_EQ(50, temp);
	ringBuffer.Consume(0, 0);

	EXPECT_EQ(1, ringBuffer.Fetch(0, temp));
	ringBuffer.Consume(0, 1);
	EXPECT_EQ(51, temp);

	EXPECT_EQ(Collections::RingBuffer<int32_t>::InvalidIndex, ringBuffer.Fetch(0, temp));

	EXPECT_EQ(4, ringBuffer.Reserve(1, 4));

	EXPECT_TRUE(ringBuffer.PushBack(1, 50));
	EXPECT_TRUE(ringBuffer.PushBack(1, 51));
	EXPECT_TRUE(ringBuffer.PushBack(1, 52));
	EXPECT_TRUE(ringBuffer.PushBack(1, 53));

	EXPECT_EQ(2, ringBuffer.Fetch(0, temp));
	EXPECT_EQ(50, temp);
	ringBuffer.Consume(0, 2);

	EXPECT_EQ(3, ringBuffer.Fetch(0, temp));
	EXPECT_EQ(51, temp);
	ringBuffer.Consume(0, 3);

	EXPECT_EQ(4, ringBuffer.Fetch(0, temp));
	EXPECT_EQ(52, temp);
	ringBuffer.Consume(0, 4);

	EXPECT_EQ(5, ringBuffer.Fetch(0, temp));
	EXPECT_EQ(53, temp);
	ringBuffer.Consume(0, 5);

	EXPECT_EQ(Collections::RingBuffer<int32_t>::InvalidIndex, ringBuffer.Fetch(0, temp));
}
