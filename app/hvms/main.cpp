#include <system/soc.hpp>
#include <utils/bytes.hpp>

// Generated HVM book initialization

#include <stdint.h>
#include "Runtime.c"

// Definition: fib
static Term fib_nodes[] = {
  {0x00000001, 0x00000005},{0x00000003, 0x0000030F},{0x00000003, 0x00000001},{0x00000000, 0x00000002},
  {0x00000000, 0x0000000C},{0x00000001, 0x0000000C},{0x00000001, 0x00000009},
};

// Definition: fib_sum
static Term fib_sum_nodes[] = {
  {0x00000001, 0x00000005},{0x00000003, 0x00000008},{0x0000000A, 0x00000001},{0x00000000, 0x00000002},
  {0x00000005, 0x0000000A},{0x00000001, 0x0000000C},{0x00000000, 0x00000002},{0x00000006, 0x00000001},
  {0x00000009, 0x0000000A},{0x0000000C, 0x00000001},{0x00000000, 0x00000002},{0x00000003, 0x00000001},
  {0x00000000, 0x00000002},
};
static Term fib_sum_rbag[] = {
  {0x00000007, 0x00000006},{0x00000000, 0x00000009},{0x0000000B, 0x00000006},{0x00000000, 0x00000009},
};

// Definition: main
static Term main_nodes[] = {
  {0x00000002, 0x00000001},{0x00000003, 0x00000007},{0x00000000, 0x00000002},{0x00000000, 0x0000000C},
  {0x00000005, 0x00000007},{0x00000002, 0x0000000C},{0x00000007, 0x00000007},{0x00000004, 0x0000000C},
  {0x00000006, 0x0000000C},
};
static Term main_rbag[] = {
  {0x00000001, 0x00000006},{0x00000000, 0x00000009},
};

static Def definitions[] = {
  {
    .name = "fib",
    .nodes = fib_nodes,
    .nodes_len = 7,
    .rbag = nullptr,
    .rbag_len = 0
  },
  {
    .name = "fib_sum",
    .nodes = fib_sum_nodes,
    .nodes_len = 13,
    .rbag = fib_sum_rbag,
    .rbag_len = 4
  },
  {
    .name = "main",
    .nodes = main_nodes,
    .nodes_len = 9,
    .rbag = main_rbag,
    .rbag_len = 2
  },
};

int
main()
{
    using namespace std::chrono_literals;

    soc::init();

    soc::uart.write(utils::to_bytes("Hello Vexii!\n"));

    hvm_init();
    BOOK.defs = definitions;
    BOOK.len = 3;
    BOOK.cap = 3;
    Term main = term_new(REF, 0, 2);
    normalize(main);
    print_node(0);
    hvm_free();

    soc::uart.write(utils::to_bytes("Done!\n"));
}
