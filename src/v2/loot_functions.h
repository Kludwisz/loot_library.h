#ifndef _LOOT_FUNCTIONS_H
#define _LOOT_FUNCTIONS_H

#include "rng.h"
#include <inttypes.h>

// ----------------------------------------------------------------------------------------

typedef enum MCVersion MCVersion;
typedef enum ItemType ItemType;
typedef enum Enchantment Enchantment;

typedef struct EnchantInstance EnchantInstance;
struct EnchantInstance {
	int enchantment;
	int level;
};

typedef struct ItemStack ItemStack;
struct ItemStack {
	int item;
	int count;

	int enchantment_count;
	EnchantInstance enchantments[16]; // 12 is the theoretical maximum for 1.17 and below, 16 should be safe for all versions
};

// ----------------------------------------------------------------------------------------

typedef int (*RollCountFunction)(uint64_t*, const int, const int);

typedef struct LootFunction LootFunction;
struct LootFunction {
	// actual function pointer
	void (*fun)(uint64_t* rand, ItemStack* is, const void* params);
	// pointer to the param array used by the function
	const void* params;

	// predefined function parameter arrays
	int params_int[2];			// for simple functions
	int* varparams_int;			// for enchantRandomly
	int** varparams_int_arr;	// for enchantWithLevels
	int varparams_int_arr_size;	// for cleaning up after enchantWithLevels
};

// ----------------------------------------------------------------------------------------
// Roll count choice functions

static inline int roll_count_constant(uint64_t* rand, const int min, const int max)
{
	return min;
}

static inline int roll_count_uniform(uint64_t* rand, const int min, const int max)
{
	const int bound = max - min + 1;
	return nextInt(rand, bound) + min;
}

// ----------------------------------------------------------------------------------------
// Loot function initializers

void create_set_count(LootFunction* lf, const int min, const int max);
void create_set_effect(LootFunction* lf);
void create_set_damage(LootFunction* lf);
void create_skip_calls(LootFunction* lf, const int skip_count);
void create_no_op(LootFunction* lf);
void create_enchant_randomly_one_enchant(LootFunction* lf, const Enchantment enchantment);
void create_enchant_randomly_list(LootFunction* lf, const Enchantment* list, const int list_length);
void create_enchant_randomly(LootFunction* lf, const MCVersion version, const ItemType item, const int isTreasure);
void create_enchant_randomly_tag(LootFunction* lf, const MCVersion version, const ItemType item, const char* tag, const int allowTreasure);
void create_enchant_with_levels(LootFunction* lf, const MCVersion version, const char* item_name, const ItemType item_type, const int min_level, const int max_level, const int isTreasure);
void create_enchant_with_levels_tag(LootFunction* lf, const MCVersion version, const char* item_name, const ItemType item_type, const int min_level, const int max_level, const char* tag, const int allowTreasure);

const char* get_enchantment_name(const Enchantment enchantment);

// ----------------------------------------------------------------------------------------
// Enums

enum MCVersion {
	v1_13,
	v1_14,
	v1_15,
	v1_16,
	v1_17,
	v1_18,
	v1_19,
	v1_20,
	v1_21
};

enum ItemType {
	NO_ITEM,
	HELMET,
	CHESTPLATE,
	LEGGINGS,
	BOOTS,
	SWORD,
	PICKAXE,
	SHOVEL,
	AXE,
	HOE,
	FISHING_ROD,
	BOW,
	CROSSBOW,
	TRIDENT,
	MACE,
	BOOK,
	SPEAR
};

enum Enchantment {
	NO_ENCHANTMENT = 0,

	// armor

	PROTECTION,
	FIRE_PROTECTION,
	BLAST_PROTECTION,
	PROJECTILE_PROTECTION,
	RESPIRATION,
	AQUA_AFFINITY,
	THORNS,
	SWIFT_SNEAK,
	FEATHER_FALLING,
	DEPTH_STRIDER,
	FROST_WALKER,
	SOUL_SPEED,

	// swords

	SHARPNESS,
	SMITE,
	BANE_OF_ARTHROPODS,
	KNOCKBACK,
	FIRE_ASPECT,
	LOOTING,
	SWEEPING_EDGE,

	// tools

	EFFICIENCY,
	SILK_TOUCH,
	FORTUNE,

	// fishing rods

	LUCK_OF_THE_SEA,
	LURE,

	// bows

	POWER,
	PUNCH,
	FLAME,
	INFINITY_ENCHANTMENT,

	// crossbows

	QUICK_CHARGE,
	MULTISHOT,
	PIERCING,

	// tridents

	IMPALING,
	RIPTIDE,
	LOYALTY,
	CHANNELING,

	// maces

	DENSITY,
	BREACH,
	WIND_BURST,

	// general

	MENDING,
	UNBREAKING,
	CURSE_OF_VANISHING,
	CURSE_OF_BINDING,

	// 1.21.11+
	LUNGE
};

// test TODO remove
void test_enchant_vec();

#endif
