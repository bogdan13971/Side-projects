#include <vector>

#define BENCHMARK_STATIC_DEFINE

#include <benchmark/benchmark.h>

static char* MAX_MATCH_BUFFER = nullptr;
static char* NO_MATCH_BUFFER = nullptr;
static char* PARTIAL_MATCH_BUFFER = nullptr;

static const int BUFFER_SIZE = 1024;
static const int MATCH_SIZE = 255;
static const int PARTIAL_MATCH_SIZE = 130;
static const int LOOKAHEAD_INDEX = MATCH_SIZE + 1;
static const int SEARCH_INDEX = 0;

#define CREATE_BENCH(FUNC) \
	[](benchmark::State& state) \
	{\
		for (auto _ : state) \
		{\
			const char* buffer = nullptr; \
			benchmark::DoNotOptimize(buffer); \
			benchmark::ClobberMemory(); \
			if(state.range(0) == 1) buffer = MAX_MATCH_BUFFER; \
			else if(state.range(0) == 2) buffer = NO_MATCH_BUFFER; \
			else buffer = PARTIAL_MATCH_BUFFER; \
			FUNC(buffer, SEARCH_INDEX, LOOKAHEAD_INDEX, MATCH_SIZE); \
		}\
	}

#define CREATE_BENCH_NAME(FUNC) "BENCH_" #FUNC

int for_loop_byte(const char* buffer, int search, int lookahead, int max);
int while_loop_byte(const char* buffer, int search, int lookahead, int max);
int while_loop_int(const char* buffer, int search, int lookahead, int max);
int while_loop_zlib(const char* buffer, int search, int lookahead, int max);
int while_loop_less_vars(const char* buffer, int search, int lookahead, int max);
int mismatch_byte(const char* buffer, int search, int lookahead, int max);
int simd(const char* buffer, int search, int lookahead, int max);
int avx(const char* buffer, int search, int lookahead, int max);
int multiple_ifs(const char* buffer, int search, int lookahead, int max);
int memcmp_inc(const char* buffer, int search, int lookahead, int max);
int memcmp_inc_opt(const char* buffer, int search, int lookahead, int max);
int memcmp_dec(const char* buffer, int search, int lookahead, int max);

void create_buffers()
{
	MAX_MATCH_BUFFER = new char[BUFFER_SIZE] {};
	NO_MATCH_BUFFER = new char[BUFFER_SIZE] {};
	PARTIAL_MATCH_BUFFER = new char[BUFFER_SIZE] {};
	
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		MAX_MATCH_BUFFER[i] = 'X';
		NO_MATCH_BUFFER[i] = 'X';
		PARTIAL_MATCH_BUFFER[i] = 'X';
	}

	for (int i = LOOKAHEAD_INDEX; i < LOOKAHEAD_INDEX + MATCH_SIZE; i++)
	{
		NO_MATCH_BUFFER[i] = '0';
	}

	for (int i = LOOKAHEAD_INDEX + PARTIAL_MATCH_SIZE; i < LOOKAHEAD_INDEX + MATCH_SIZE; i++)
	{
		PARTIAL_MATCH_BUFFER[i] = '0';
	}
}

void delete_buffers()
{
	delete[] MAX_MATCH_BUFFER;
	delete[] NO_MATCH_BUFFER;
	delete[] PARTIAL_MATCH_BUFFER;
}

int main(int argc, char* argv[])
{
	create_buffers();

	std::vector<const char*> function_names = {
		CREATE_BENCH_NAME(for_loop_byte),
		CREATE_BENCH_NAME(while_loop_byte),
		CREATE_BENCH_NAME(while_loop_int),
		CREATE_BENCH_NAME(while_loop_zlib),
		CREATE_BENCH_NAME(while_loop_less_vars),
		CREATE_BENCH_NAME(mismatch_byte),
		CREATE_BENCH_NAME(simd),
		CREATE_BENCH_NAME(avx),
		CREATE_BENCH_NAME(multiple_ifs),
		CREATE_BENCH_NAME(memcmp_inc),
		CREATE_BENCH_NAME(memcmp_inc_opt),
		CREATE_BENCH_NAME(memcmp_dec),
	};

	using FUNC_TYPE = std::function<void(benchmark::State&)>;

	std::vector<FUNC_TYPE> functions = {
		CREATE_BENCH(for_loop_byte),
		CREATE_BENCH(while_loop_byte),
		CREATE_BENCH(while_loop_int),
		CREATE_BENCH(while_loop_zlib),
		CREATE_BENCH(while_loop_less_vars),
		CREATE_BENCH(mismatch_byte),
		CREATE_BENCH(simd),
		CREATE_BENCH(avx),
		CREATE_BENCH(multiple_ifs),
		CREATE_BENCH(memcmp_inc),
		CREATE_BENCH(memcmp_inc_opt),
		CREATE_BENCH(memcmp_dec),
	};

	benchmark::MaybeReenterWithoutASLR(argc, argv);

	for (int i = 0; i < function_names.size(); i++)
	{
		auto benchmark = benchmark::RegisterBenchmark(function_names[i], functions[i]);
		benchmark->Arg(1)->Arg(2)->Arg(3);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
	benchmark::Shutdown();

	delete_buffers();

	return 0;
}

int for_loop_byte(const char* buffer, int search, int lookahead, int max)
{
	int len = 0;
	for (int i = 0; i < max; i++)
	{
		if (buffer[search + i] == buffer[lookahead + i])
		{
			len++;
		}
		else
		{
			break;
		}
	}

	return len;
}

int while_loop_byte(const char* buffer, int search, int lookahead, int max)
{
	int len = 0;
	const int end = search + max;
	while (search < end
		&& buffer[search++] == buffer[lookahead++]
		)
	{
		len++;
	}

	return len;
}

int while_loop_int(const char* buffer, int search, int lookahead, int max)
{
	using TYPE = int64_t;
	int len = 0;
	const int end = search + max;
	const int size = sizeof(TYPE);

	while (search + size < end
		&& ((const TYPE*)buffer)[search] == ((const TYPE*)buffer)[lookahead]
		)
	{
		search += size;
		lookahead += size;
		len += size;
	}

	while (search < end
		&& buffer[search++] == buffer[lookahead++]
		)
	{
		len++;
	}

	return len;
}

int while_loop_zlib(const char* buffer, int search, int lookahead, int max)
{
	const int start = search;
	const int end = search + max;

	while (search < end
		&& buffer[search++] == buffer[lookahead++]
		&& buffer[search++] == buffer[lookahead++]
		&& buffer[search++] == buffer[lookahead++]
		&& buffer[search++] == buffer[lookahead++]
		)
	{
	}

	if (search > max)
	{
		search = max;
	}

	return search - start;
}

int while_loop_less_vars(const char* buffer, int search, int lookahead, int max)
{
	using TYPE = int64_t;
	const int start = search;
	const int end = search + max;
	const int size = sizeof(TYPE);

	do {} while (search + size < end
		&& ((const TYPE*)buffer)[search += size] == ((const TYPE*)buffer)[lookahead += size]
		);

	do {} while (search < end
		&& buffer[search++] == buffer[lookahead++]
		);

	if (search > end)
	{
		search = max;
	}

	return search - start;
}

int mismatch_byte(const char* buffer, int search, int lookahead, int max)
{
	auto it = std::mismatch(buffer + search, buffer + search + max, buffer + lookahead, buffer + lookahead + max);
	return it.first - buffer;
}

int simd(const char* buffer, int search, int lookahead, int max)
{
	int len = 0;
	constexpr int block_size = 16;

	for (int i = 0; i < 16; i++)
	{
		auto p1 = reinterpret_cast<const __m128i*>(buffer + search + i * 16);
		auto p2 = reinterpret_cast<const __m128i*>(buffer + lookahead + i * 16);

		auto a = _mm_loadu_si128(p1);
		auto b = _mm_loadu_si128(p2);

		auto cmp = _mm_cmpeq_epi8(a, b);

		auto mask = _mm_movemask_epi8(cmp);
		if (mask == 0xFFFF)
		{
			len += 16;
		}
		else
		{
			auto diff = _tzcnt_u32(~mask);
			len += diff;
			break;
		}
	}

	return len;
}

int avx(const char* buffer, int search, int lookahead, int max)
{
	int len = 0;
	constexpr int block_size = 32;

	for (int i = 0; i < 256 / 32; i++)
	{
		auto p1 = reinterpret_cast<const __m256i*>(buffer + search + i * 32);
		auto p2 = reinterpret_cast<const __m256i*>(buffer + lookahead + i * 32);

		auto a = _mm256_loadu_si256(p1);
		auto b = _mm256_loadu_si256(p2);

		auto cmp = _mm256_cmpeq_epi8(a, b);

		auto mask = _mm256_movemask_epi8(cmp);
		if (mask == -1)
		{
			len += 32;
		}
		else
		{
			auto diff = _tzcnt_u32(~mask);
			len += diff;
			break;
		}
	}

	return len;
}

int multiple_ifs(const char* buffer, int search, int lookahead, int max)
{
	using TYPE = int64_t;
	int len = 0;
	const int size = sizeof(TYPE);
	const TYPE* buff = reinterpret_cast<const TYPE*>(buffer);
	const TYPE* p1 = reinterpret_cast<const TYPE*>(buffer + search);
	const TYPE* p1_orig = reinterpret_cast<const TYPE*>(buffer + search);
	const TYPE* p2 = reinterpret_cast<const TYPE*>(buffer + lookahead);
	const TYPE* end = reinterpret_cast<const TYPE*>(buffer + search + max);

	//compare as int64
	while (
		p1 < end
		&& *(p1++) == *(p2++) //first 8 bytes
		&& *(p1++) == *(p2++) //second 8 bytes
		&& *(p1++) == *(p2++) //third 8 bytes
		&& *(p1++) == *(p2++) //fourth 8 bytes
		)
	{
	}

	len += (p1 - p1_orig - 1) * 8;

	const char* pp1 = reinterpret_cast<const char*>(p1 - 1);
	const char* pp1_orig = reinterpret_cast<const char*>(p1 - 1);
	const char* pp2 = reinterpret_cast<const char*>(p2 - 1);
	const char* ppend = buffer + search + max;

	//compare as char
	while (
		pp1 < ppend
		&& *(pp1++) == *(pp2++) //first byte
		&& *(pp1++) == *(pp2++) //second byte
		&& *(pp1++) == *(pp2++) //third byte
		&& *(pp1++) == *(pp2++) //fourth byte
		)
	{
	}

	len += (pp1 - pp1_orig - 1);

	return len;
}

int memcmp_inc(const char* buffer, int search, int lookahead, int max)
{
	int len = 0;

	const char* start = buffer + search;
	const char* s_search = buffer + search;
	const char* s_look = buffer + lookahead;

	const int block = 16;

	while (s_search + block < buffer + search + max
		&& memcmp(s_search, s_look, block) == 0)
	{
		s_search += block;
		s_look += block;
		len += block;
	};

	while (s_search < buffer + search + max
		&& *(s_search++) == *(s_look++)
		)
	{
		len++;
	}

	return len;
}

int memcmp_inc_opt(const char* buffer, int search, int lookahead, int max)
{
	int len = 0;

	const char* start = buffer + search;
	const char* s_search = buffer + search;
	const char* s_look = buffer + lookahead;

	int block = 16;

	while (s_search + block < buffer + search + max
		&& memcmp(s_search, s_look, block) == 0)
	{
		s_search += block;
		s_look += block;
		len += block;
	};

	block >>= 1;
	if (memcmp(s_search, s_look, block) == 0)
	{
		s_search += block;
		s_look += block;
		len += block;
	}

	block >>= 1;
	if (memcmp(s_search, s_look, block) == 0)
	{
		s_search += block;
		s_look += block;
		len += block;
	}

	while (s_search < buffer + search + max
		&& *(s_search++) == *(s_look++)
		)
	{
		len++;
	}

	return len;
}

int memcmp_dec(const char* buffer, int search, int lookahead, int max)
{
	int len = 0;

	const char* start = buffer + search;
	const char* s_search = buffer + search;
	const char* s_look = buffer + lookahead;

	int block = 128;
	const int min_block = 4;

	while (max > 0 && block > min_block)
	{
		if (memcmp(s_search, s_look, std::min(block, max)) == 0)
		{
			s_search += block;
			s_look += block;
			len += block;
			max -= block;
		}
		else
		{
			block >>= 1;
		}
	}

	while (max--
		&& *(s_search++) == *(s_look++)
		)
	{
		len++;
	}

	return len;
}
