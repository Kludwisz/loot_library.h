#include "loot_table_context.h"
#include <string.h>


void set_loot_seed(LootTableContext* context, uint64_t seed)
{
	context->prng_state = (seed ^ 0x5deece66dULL) & 0xffffffffffffULL;
}

void set_internal_loot_seed(LootTableContext* context, uint64_t internal_seed)
{
	context->prng_state = internal_seed;
}

int get_item_id(LootTableContext* context, const char* item_name)
{
	for (int i = 0; i < context->item_count; i++)
	{
		if (strcmp(context->item_names[i], item_name) == 0)
			return i;
	}
	return -1;
}

const char* get_item_name(LootTableContext* context, int item_id)
{
	if (item_id < 0 || item_id >= context->item_count)
		return NULL;
	return context->item_names[item_id];
}

// ------------------------------------------------------------------------

void generate_loot(LootTableContext* context)
{
	// this is the entire point of the library.
	context->generated_item_count = 0;
	
	for (int loot_pool = 0; loot_pool < context->pool_count; loot_pool++)
	{
		const LootPool* pool = &(context->loot_pools[loot_pool]);

		// each loot pool first chooses the number of rolls
		RollCountFunction roll_choice = pool->roll_count_function;
		const int rolls = roll_choice(&(context->prng_state), pool->min_rolls, pool->max_rolls);

		for (int r = 0; r < rolls; r++)
		{
			// roll a weighted random entry
			int w = nextInt(&context->prng_state, pool->total_weight);
			int entry = pool->precomputed_loot[w];
			int item = pool->entry_to_item[entry];
			if (item == -1)
				continue;

			// add the non-empty entry as a generated item
			ItemStack* item_stack = &context->generated_items[context->generated_item_count];
			(context->generated_item_count)++;
			item_stack->item = item;
			item_stack->count = 1;
			item_stack->enchantment_count = 0;

			// sequentially apply all the loot functions to the item stack
			const int function_count = pool->entry_functions_count[entry];
			const int function_index = pool->entry_functions_index[entry];
			for (int f = 0; f < function_count; f++)
			{
				LootFunction* lf = &pool->loot_functions[function_index + f];
				lf->fun(&context->prng_state, item_stack, lf->params);
			}
		}
	}
}
