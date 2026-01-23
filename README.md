# loot_library.h
A C library for emulating Minecraft loot table generation.

While it's written in C, the entire library can be ported to CUDA very easily if needed.

# Example
Taken from `src/examples/example.c`.
```C
#include <stdio.h>

#include "../mc_loot.h"

static void print_loot(LootTableContext* ctx)
{
    for (int i = 0; i < ctx->generated_item_count; i++)
    {
        ItemStack* item_stack = &(ctx->generated_items[i]);
        printf("%s x %d\n", get_item_name(ctx, item_stack->item), item_stack->count);

        for (int j = 0; j < item_stack->enchantment_count; j++)
        {
            EnchantInstance* ench = &(item_stack->enchantments[j]);
            printf("    %s %d\n", get_enchantment_name(ench->enchantment), ench->level);
        }
    }
}

int main()
{
    LootTableContext ctx;
    FILE* fptr = fopen("shipwreck_supply.json", "rb");
    init_loot_table_file(fptr, &ctx, (MCVersion)v1_21);
    free(fptr);
    set_loot_seed(&ctx, -617667753675473930ULL);
    generate_loot(&ctx);
    print_loot(&ctx);
    free_loot_table(&ctx);
    return 0;
}
```

# TODO
## Update 1
- [x] load directly from FILE* instead of const char* to avoid relative filepath issues
- [x] set_effect loot function (skips the effect call)
- [x] chained loot tables

## Update 2
- [ ] multiple operation modes for LootTableContext: as-is, aggregated matching items, aggregated item-type matching items, predicate-match, full (indexed)

## Update 3
- [ ] loot sequence support
- [x] restructure project: move legacy code to a subfolder (src/legacy?)
- [x] update readme with v2 example of use

## Update 4
- [x] full 1.13+ support (excluding 1.14.2)
- [ ] mass testing using source code
- [ ] add more examples in src/examples
