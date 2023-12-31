/*
 *  triemaker.h
 *  
 *  Created by Javid Mann on 09/06/2023.
 *
 */

struct TrieNode {
	char terminal;
	char index;
	struct Character* entry;
};

struct Character {
	char letter;
	struct TrieNode* next;
};

int printNodes(FILE* file, struct TrieNode* node, int start);
int findNodeLength(struct TrieNode* node);
int findNodeLengthRecursive(struct TrieNode* node, int length);

const char* words[] = {
	"a",
	"akesi",
	"ala",
	"alasa",
	"ale",
	"anpa",
	"ante",
	"anu",
	"awen",
	"e",
	"en",
	"esun",
	"ijo",
	"ike",
	"ilo",
	"insa",
	"jaki",
	"jan",
	"jelo",
	"jo",
	"kala",
	"kalama",
	"kama",
	"kasi",
	"ken",
	"kepeken",
	"kijetesantakalu",
	"kili",
	"kin",
	"kipisi",
	"kiwen",
	"ko",
	"kon",
	"ku",
	"kule",
	"kulupu",
	"kute",
	"la",
	"lape",
	"laso",
	"lawa",
	"leko",
	"len",
	"lete",
	"li",
	"lili",
	"linja",
	"lipu",
	"loje",
	"lon",
	"luka",
	"lukin",
	"lupa",
	"ma",
	"mama",
	"mani",
	"meli",
	"mi",
	"mije",
	"moku",
	"moli",
	"monsi",
	"monsuta",
	"mu",
	"mun",
	"musi",
	"mute",
	"namako",
	"nanpa",
	"nasa",
	"nasin",
	"nena",
	"ni",
	"nimi",
	"noka",
	"o",
	"olin",
	"ona",
	"open",
	"pakala",
	"pali",
	"palisa",
	"pan",
	"pana",
	"pi",
	"pilin",
	"pimeja",
	"pini",
	"pipi",
	"poka",
	"poki",
	"pona",
	"pu",
	"sama",
	"seli",
	"selo",
	"seme",
	"sewi",
	"sijelo",
	"sike",
	"sin",
	"sina",
	"sinpin",
	"sitelen",
	"soko",
	"sona",
	"soweli",
	"suli",
	"suno",
	"supa",
	"suwi",
	"tan",
	"taso",
	"tawa",
	"telo",
	"tenpo",
	"toki",
	"tomo",
	"tonsi",
	"tu",
	"unpa",
	"uta",
	"utala",
	"walo",
	"wan",
	"waso",
	"wawa",
	"weka",
	"wile"};