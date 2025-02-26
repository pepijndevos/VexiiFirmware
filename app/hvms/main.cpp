#include <system/soc.hpp>
#include <utils/bytes.hpp>

// Generated HVM book initialization

#include <stdint.h>
#include "Runtime.c"

unsigned int get_hart_id(void) {
    unsigned int hartid;
    asm volatile("csrr %0, mhartid" : "=r" (hartid));
    return hartid;
}

// Definition: fib
static Term fib_nodes[] = {
  0x0000000100000005,0x000000030000030F,0x0000000300000001,0x0000000000000002,
  0x000000000000000C,0x000000010000000C,0x0000000100000009,
};

// Definition: fib_sum
static Term fib_sum_nodes[] = {
  0x0000000100000005,0x0000000300000008,0x0000000A00000001,0x0000000000000002,
  0x000000050000000A,0x000000010000000C,0x0000000000000002,0x0000000600000001,
  0x000000090000000A,0x0000000C00000001,0x0000000000000002,0x0000000300000001,
  0x0000000000000002,
};
static Term fib_sum_rbag[] = {
  0x0000000700000006,0x0000000000000009,0x0000000B00000006,0x0000000000000009,
};

// Definition: main
static Term main_nodes[] = {
  0x0000000200000001,0x0000000300000007,0x0000000000000002,0x000000000000000C,
  0x0000000500000007,0x000000020000000C,0x0000000700000007,0x000000040000000C,
  0x000000060000000C,
};
static Term main_rbag[] = {
  0x0000000100000006,0x0000000000000009,
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

    a64* counter = (a64*)0xA0000000;
    atomic_store(counter, 0);

    soc::init();

    char buf[10];
    soc::uart.write(utils::to_bytes("Hello Vexii!\n"));

    for(int i=0; i<10; i++) {
      itoa(atomic_load(counter), buf, 10);
      soc::uart.write(utils::to_bytes(buf));
      soc::uart.write(utils::to_bytes("\n"));

      atomic_fetch_add(counter, 1);
    }

    while(atomic_load(counter) < 20);

    main_nodes[3] |= ((Term)get_hart_id()) << 34;

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
