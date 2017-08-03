import json
from pprint import pprint

with open("cr_json.json") as data_file:
	cd = json.load(data_file)
with open("deck.txt") as f:
	content = f.readlines()
deck_list = [x.strip() for x in content]
pprint(deck_list)
print("\n\n\n")
deck = {}
for card in deck_list:
	card_info = card.split(',')
	card_name = card_info[0]
	print(card_name)
	card_lvl  = int(card_info[1])
	card_data = cd[card_name]
	deck[card_name] = {'cost':card_data['cost'],
					   'power':card_data['levels'][card_lvl-1],
					   'type':card_data['type']}
pprint(deck)
