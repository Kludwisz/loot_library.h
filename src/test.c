#include "mc_loot.h"
#include <stdio.h>


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

int test_shipwreck() {
	LootTableContext ctx;

	FILE* file = fopen("src/examples/shipwreck_supply.json", "r");
	int ret = init_loot_table_file(file, &ctx, (MCVersion)v1_21);
	fclose(file);

	if (ret != 0) {
		fprintf(stderr, "Error initializing loot table\n");
		return ret;
	}

	set_loot_seed(&ctx, 123456ULL);
	generate_loot(&ctx);
	print_loot(&ctx);
	free_loot_table(&ctx);

	return 0;
}

int test_ominous_vault() {
	LootTableContext ctx;

	FILE* file = fopen("src/examples/chained_tables/reward_ominous.json", "r");
	int ret = init_loot_table_file(file, &ctx, (MCVersion)v1_21);
	fclose(file);
	if (ret != 0) {
		fprintf(stderr, "Error initializing loot table\n");
		return ret;
	}

	// resolve subtables in the correct order: rare, common, unique
	file = fopen("src/examples/chained_tables/reward_ominous_rare.json", "r");
	ret = resolve_subtable_file(&ctx, "minecraft:chests/trial_chambers/reward_ominous_rare", file);
	fclose(file);
	if (ret != 0) {
		fprintf(stderr, "Error resolving subtable\n");
		return ret;
	}

	file = fopen("src/examples/chained_tables/reward_ominous_common.json", "r");
	ret = resolve_subtable_file(&ctx, "minecraft:chests/trial_chambers/reward_ominous_common", file);
	fclose(file);
	if (ret != 0) {
		fprintf(stderr, "Error resolving subtable\n");
		return ret;
	}

	file = fopen("src/examples/chained_tables/reward_ominous_unique.json", "r");
	ret = resolve_subtable_file(&ctx, "minecraft:chests/trial_chambers/reward_ominous_unique", file);
	fclose(file);
	if (ret != 0) {
		fprintf(stderr, "Error resolving subtable\n");
		return ret;
	}

	set_loot_seed(&ctx, 123456ULL);
	generate_loot(&ctx);
	print_loot(&ctx);
	free_loot_table(&ctx);

	return 0;
}

int test_desert_temple()
{
	LootTableContext ctx;

	FILE* file = fopen("src/examples/desert_pyramid.json", "r");
	int ret = init_loot_table_file(file, &ctx, (MCVersion)v1_18);
	fclose(file);
	if (ret != 0) {
		fprintf(stderr, "Error initializing loot table\n");
		return ret;
	}

	// /setblock 3100 51 -2774 minecraft:chest[facing=west,type=single,waterlogged=false]{LootTable:"minecraft:chests/desert_pyramid",LootTableSeed:-6618568904386583729L,components:{}}
	// /setblock 3098 51 -2772 minecraft:chest[facing=north,type=single,waterlogged=false]{LootTable:"minecraft:chests/desert_pyramid",LootTableSeed:-4350686274204906785L,components:{}}
	// /setblock 3096 51 -2774 minecraft:chest[facing=east,type=single,waterlogged=false]{LootTable:"minecraft:chests/desert_pyramid",LootTableSeed:-1674741226462785893L,components:{}}
	for (int64_t lootSeed = 1LL; lootSeed <= 20LL; lootSeed++)
	{
		set_loot_seed(&ctx, lootSeed);
		generate_loot(&ctx);
		printf("[%lld]\n", lootSeed);
		print_loot(&ctx);
	}
	
	
	free_loot_table(&ctx);
    return 0;
}

int test_ancient_city()
{
	LootTableContext ctx;

	FILE* file = fopen("src/examples/ac_1_21_11.json", "r");
	int ret = init_loot_table_file(file, &ctx, (MCVersion)v1_21_11);
	fclose(file);
	if (ret != 0) {
		fprintf(stderr, "Error initializing loot table\n");
		return ret;
	}

	int64_t lootSeed = 4521007606537734820LL;
	set_loot_seed(&ctx, lootSeed);
	generate_loot(&ctx);
	print_loot(&ctx);

	free_loot_table(&ctx);
    return 0;
}

int test_bt()
{
	LootTableContext ctx;

	FILE* file = fopen("src/examples/buried_treasure.json", "r");
	int ret = init_loot_table_file(file, &ctx, (MCVersion)v1_21);
	fclose(file);
	if (ret != 0) {
		fprintf(stderr, "Error initializing loot table\n");
		return ret;
	}

	int64_t lootSeed = 6249925021267101877ULL;
	set_loot_seed(&ctx, lootSeed);
	generate_loot(&ctx);
	print_loot(&ctx);

	free_loot_table(&ctx);
    return 0;
}

int test_bastion_other() {
	LootTableContext ctx;

	FILE* file = fopen("src/examples/bastion_other.json", "r");
	int ret = init_loot_table_file(file, &ctx, (MCVersion)v1_21);
	fclose(file);
	if (ret != 0) {
		fprintf(stderr, "Error initializing loot table\n");
		return ret;
	}

	int64_t lootSeed = -7285891695222447769LL;
	set_loot_seed(&ctx, lootSeed);
	generate_loot(&ctx);
	print_loot(&ctx);

	free_loot_table(&ctx);
    return 0;
}

int test_jungle_dispenser() {
	LootTableContext ctx;

	FILE* file = fopen("src/examples/jungle_dispenser.json", "r");
	int ret = init_loot_table_file(file, &ctx, (MCVersion)v1_21);
	fclose(file);
	if (ret != 0) {
		fprintf(stderr, "Error initializing loot table\n");
		return ret;
	}

	int64_t lootSeed = -1076206504761598326LL;
	set_loot_seed(&ctx, lootSeed);
	generate_loot(&ctx);
	print_loot(&ctx);

	free_loot_table(&ctx);
    return 0;
}

int main()
{
	test_ancient_city();


	//test_jungle_dispenser();
	//test_bastion_other();
	//print_enchant_randomly_rp();
	//test_bt();
	//test_ancient_city();
	//test_enchant_vec();
	//test_desert_temple();
	//test_shipwreck();
	//test_ominous_vault();
}
