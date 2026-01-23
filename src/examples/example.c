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
