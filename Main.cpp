#include <iostream>
#include <vector>
// Tato knihovna slouzi ke tvorbe vektoru
#include <string>
#include <cstdlib>
#include <ctime>
// Tato knihovna slouží ke zpomalení chodu kodu
#include <windows.h>
// Tato knihovna slouží k mazani jiz nepotrebnych vypisu
#include <algorithm>
// Tato knihovna slouží ke tvorbe algoritmu
#include <random>
// Tato knihovna slouží k tomu abych ve hre mohl mit hody kostkou
using namespace std;

// --- Herni struktury ---

// Struktury jsou v podstate takove skupiny co pod sebe mohou vzit vice promených a tvorit tak komplexnější systém se kterým se lépe pracuje
struct Ability {
    string name;
    string desc;
    int damage;
};

struct Player {
    string name;
    string player_class;
    int max_hp;
    int hp;
    int heal;
    int resistance;
    int gold;
    int level;
    int exp;
    int attack;
    vector<Ability> abilities;
};

struct Reward {
    int gold;
    int exp;
};

struct Enemy {
    string name;
    int hp;
    int attack;
    bool miniboss;
    bool boss;
};

struct Village {
    string name;
};

enum EncounterType { ENEMY1, ENEMY2, ENEMY3, MINIBOSS, BOSS, VILLAGE };

struct Encounter {
    EncounterType type;
    int count;
    string name;
};
// Tato struktura slouzi pro tvorbu jednoduche herni mapy se kterou se velmi jednodnoduse manipuluje. Tohle řešení mi doporučilo AI (bohužel už si nepamatuju prompt)
// --- Herni mapa ---
vector<Encounter> game_map = {
    {VILLAGE, 0, "Vesnice U Prvni Zaby"},
    {ENEMY1, 1, ""},
    {ENEMY2, 2, ""},
    {VILLAGE, 0, "Vesnice U Druhe Zaby"},
    {ENEMY3, 3, ""},
    {MINIBOSS, 1, "MiniBoss: Slimak"},
    {VILLAGE, 0, "Vesnice U Treti Zaby"},
    {ENEMY1, 1, ""},
    {ENEMY2, 2, ""},
    {VILLAGE, 0, "Vesnice U Ctvrte Zaby"},
    {MINIBOSS, 1, "MiniBoss: Krab"},
    {ENEMY3, 3, ""},
    {VILLAGE, 0, "Vesnice U Pate Zaby"},
    {BOSS, 1, "NENAVIDIMK0LOSTESTI"}
};

vector<string> enemy_names = {
    "Kostlivec", "Goblin", "Netopyr", "Zluty Krab", "Zeleny Slimak"
};

// --- Pomocné funkce ---
void clear() { system("cls"); }
void clear_and_wait(int ms) {
    clear();
    Sleep(ms);
    }
// Tato funkce slouží k lepší čitelnosti a srozumitelnosti hry

void print_player_stats(const Player& p) {
    cout << "Classa: " << p.player_class << " | Level: " << p.level << " | HP: " << p.hp << "/" << p.max_hp << " | Odolnost: " << p.resistance
         << " | Gold: " << p.gold << " | EXP: " << p.exp << endl;
}

void print_abilities(const Player& p) {
    cout << "Schopnosti:" << endl;
    for (size_t i = 0; i < p.abilities.size(); ++i) {
        cout << i+1 << ": " << p.abilities[i].name << " - " << endl << p.abilities[i].desc
             << " (DMG: " << p.abilities[i].damage << ")" << endl;
    }
}

// --- Výběr classy ---
void class_selection(Player& p) {
    string input;
    int proces = 1;
    do {
        cout << "Vyber si classu (zadej presne nazev):" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "konzolovy_uzivatel: vetsinu her hrajes na konzily a proto by si nemusel zvladnout obtiznoust ostatnich class." << endl
        << "sila = 8 | odolnost = 15 | stamina = 2 | rychlost = 8 | bandaze = 6 | hp = 80" << endl << endl;
        cout << "skleneny_kanon: tvoje sila je obrovska, ale tvoje telo prekvapive krehke." << endl
        << "sila = 12 | odolnost = 8 | stamina = 1 | rychlost = 10 | bandaze = 8 | hp = 35" << endl << endl;
        cout << "proc_ma_vsechno_tolik_hp: i pitomeho komara budes mlatit hodne dlouho" << endl
        << "sila = 3 | odolnost = 12 | stamina = 2 | rychlost = 5 | bandaze = 8 | hp = 60" << endl;
        cout << "-----------------------------------------" << endl;
        cin >> input;
        if (input == "konzolovy_uzivatel") {
            p.player_class = "konzolovy_uzivatel";
            p.max_hp = 80; p.hp = 80; p.heal = 6; p.attack = 8; p.resistance = 15; p.gold = 10; p.level = 1; p.exp = 0;
            p.abilities = {
                {"Mackani tlacitek", "Provedes normalni kombo", 2},
                {"Mackani tlacitek tvrdeji", "Provedes op kombo", 3},
                {"Pouzit Bandaze", "Pouzijes bandaze co ti muzou pridat az 24 hp", 0}
            };
        } else if (input == "skleneny_kanon") {
            p.player_class = "skleneny_kanon";
            p.max_hp = 35; p.hp = 35; p.heal = 8; p.attack = 12; p.resistance = 8; p.gold = 10; p.level = 1; p.exp = 0;
            p.abilities = {
                {"Zvuky praskani skla", "Jako zazrakem se t nic nestane", 3},
                {"Skleneny uder", "Asi si z tvrzeneho skla", 6},
                {"Pouzit Bandaze", "Pouzijes bandaze co ti muzou pridat az 24 hp", 0}
            };
        } else if (input == "proc_ma_vsechno_tolik_hp") {
            p.player_class = "proc_ma_vsechno_tolik_hp";
            p.max_hp = 60; p.hp = 60; p.heal = 8; p.attack = 3; p.resistance = 12; p.gold = 10; p.level = 1; p.exp = 0;
            p.abilities = {
                {"Pevny uder", "Cekal bys ze to da vic damage a ono nic", 1},
                {"Super mega uder", "Ocekavani velka, poskozeni prekvapive male", 1},
                {"Pouzit Bandaze", "Pouzijes bandaze co ti muzou pridat az 24 hp", 0}
            };
        } else {
            cout << "Neplatna volba classy. Zadej presny nazev classy!" << endl;
            continue;
        }
        cout << "Zvolil jsi classu: " << p.player_class << endl;
        print_player_stats(p);
        print_abilities(p);
        cout << "Potvrdit? (y/n): ";
        cin >> input;
        if (input == "y" || input == "Y") proces = 0;
    } while (proces == 1);
}

// --- Levelování ---
void check_level_up(Player& p) {
    int exp_needed = 20 + (p.level - 1) * 10;
    while (p.exp >= exp_needed) {
        p.exp -= exp_needed;
        p.level++;
        p.max_hp += 5; p.hp = p.max_hp;
        p.attack += 1;
        cout << "Novy level! Level: " << p.level << endl;
        cout << "Max zivot: " << p.max_hp << ", Utok: " << p.attack << endl;
        exp_needed = 20 + (p.level - 1) * 10;
    }
}

// --- Vesnice ---
void village(Player& p, const Village& v) {
    cout << "Dorazil jsi do vesnice: " << v.name << endl;
    int choice = 0;
    do{
        cout << "Co chces delat?:" << endl
        << "1: Kopit bandaze (3 zlata)" << endl
        << "2: Zvysit max zivot (10 zlata)" << endl
        << "3: Zvysit utok (15 zlata)" << endl
        << "4: Zvysit odolnost (12 zlata)" << endl
        << "5: Odejit" << endl;
    cin >> choice;
    if (choice == 1 && p.gold >= 3) {
        p.gold -= 3; p.heal += 1;
        cout << "Koupil si bandaze." << endl;
    } else if (choice == 2 && p.gold >= 10) {
        p.gold -= 10; p.max_hp += 2;
        cout << "Max zivot zvysen." << endl;
    } else if (choice == 3 && p.gold >= 15) {
        p.gold -= 15; p.attack += 1;
        cout << "Utok zvysen." << endl;
    } else if (choice == 4 && p.gold >= 12) {
        p.gold -= 12; p.resistance += 1;
        cout << "Odolnost zvysena." << endl;
    } else if (choice == 5) {
        cout << "Opoustis vesnici." << endl;
    } else {
        cout << "Nemas dost zlata nebo neplatna volba." << endl;
    }
    } while (choice != 5);
}

// --- Tvorba nepřátel ---
Enemy make_enemy(int idx, bool miniboss = false) {
    if (miniboss) {
        if (idx % 2 == 0) return {"MiniBoss: Slimak", 26, 18, true, false};
        else return {"MiniBoss: Krab", 32, 22, true, false};
    }
    return {enemy_names[idx % enemy_names.size()], 15 + rand()%5, 10 + rand()%8, false, false};
}

// Spočítá odměnu za všechny poražené nepřátele
Reward calculate_rewards(const Player& p, const vector<Enemy>& defeated_enemies) {
    int total_gold = 0;
    int total_exp = 0;
    for (const auto& e : defeated_enemies) {
        int base_gold = 0, base_exp = 0;
        if (e.boss) { base_gold = 50; base_exp = 40; }
        else if (e.miniboss) { base_gold = 20; base_exp = 15; }
        else { base_gold = 8; base_exp = 5; }
        double level_mod = 1.0 - 0.05 * (p.level - 1);
        if (level_mod < 0.5) level_mod = 0.5;
        int gold_bonus = rand() % 6; // 0–5 zlata navíc
        int exp_bonus = rand() % 4;  // 0–3 XP navíc
        total_gold += static_cast<int>(base_gold * level_mod) + gold_bonus;
        total_exp  += static_cast<int>(base_exp  * level_mod) + exp_bonus;
    }
    return {total_gold, total_exp};
}

int rand_gold(bool always) {
    if (always) return 8 + rand() % 10;
    return (rand() % 2 == 0) ? (4 + rand() % 8) : 0;
}

int roll (int max_number) {
    if (max_number <= 1) return max_number;
    return 1 + rand() % max_number;
}

// Hodí kostkou (1 až max_roll) a přičte damage ability
int roll_damage_with_ability(int max_roll, int ability_damage) {
    if (max_roll <= 1) return 1 + ability_damage;
    int kostka = 1 + rand() % max_roll;
    return kostka + ability_damage;
}

// Funkce pro výpočet skutečného poškození po odečtení odolnosti
int apply_player_resistance(int incoming_damage, int resistance) {
    if (resistance <= 1) return incoming_damage; // žádná nebo minimální odolnost
    int hod = rand() % resistance + 1;
    int vysledek = incoming_damage - hod;
    if (vysledek < 0) vysledek = 0;
    cout << "Odolnost: hodil jsi " << hod << " na " << resistance << " , damage snizeno na " << vysledek << "." << std::endl;
    return vysledek;
}

// funkce fight:
void fight(Player& p, vector<Enemy> enemies, bool boss_first = false) {
    vector<Enemy> original_enemies = enemies;
    bool player_first = !boss_first;

    string last_player_action = "";
    vector<string> last_enemy_actions(enemies.size(), "");

    int round = 0;
    while (p.hp > 0 && !enemies.empty()) {
        if (round > 0) {
            cout << "--- Akce minuleho kola ---" << endl;
            if (!last_player_action.empty())
                cout << "Hrac: " << last_player_action << endl;
            for (size_t i = 0; i < enemies.size(); ++i) {
                if (i < last_enemy_actions.size() && !last_enemy_actions[i].empty())
                    cout << enemies[i].name << ": " << last_enemy_actions[i] << endl;
            }
            cout << "--------------------------" << endl;
        }

        for (size_t i = 0; i < enemies.size(); ++i)
            cout << i+1 << ") " << enemies[i].name << " HP: " << enemies[i].hp << endl;
        print_abilities(p);
        print_player_stats(p);
        int ability_choice = 1;
        cout << "Vyber schopnost (cislo): ";
        cin >> ability_choice;
        if (ability_choice < 1 || ability_choice > (int)p.abilities.size()) ability_choice = 1;
        Ability ab = p.abilities[ability_choice-1];

        // --- Akce hráče ---
        last_player_action = ""; // reset akce hráče pro toto kolo
        if (ab.name == "Pouzit Bandaze") {
            if (p.hp < p.max_hp && p.heal > 0) {
                int healing = roll(24);
                last_player_action = "Pouzil bandaze a vylecil se o " + to_string(healing);
                cout << "Hodil jsi " << healing << " na leceni pomoci bandazi." << endl;
                if ((p.hp + healing) > p.max_hp) {
                    p.hp = p.max_hp;
                    cout << "Doplnil sis zivoty na maximum!" << endl;
                } else {
                    p.hp += healing;
                    cout << "Doplnil sis zivoty o " << healing << endl;
                }
                p.heal--; // snížit počet bandáží!
            } else {
                last_player_action = "Zkousel pouzit bandaze, ale nemohl vylecit.";
                cout << "Bandaze nesly pouzit (mas plne HP nebo zadne bandaze)!" << endl;
            }
        } else {
            int player_dmg = roll_damage_with_ability(p.attack, ab.damage);
            last_player_action = "Pouzil " + ab.name + " a hodil " + to_string(player_dmg) + " (kostka max " + to_string(p.attack) + " + ability " + to_string(ab.damage) + ")";
            cout << "Hodil jsi na utok: " << player_dmg << " (kostka max " << p.attack << " + ability " << ab.damage << ")" << endl;
        if (ab.name == "Zabaci kop" || ab.name == "Skleneny uder" || ab.name == "Dlouhe mlaceni") {
            if (!enemies.empty()) enemies[0].hp -= player_dmg;
        } else {
            for (size_t i = 0; i < enemies.size(); ++i) {
                if (enemies[i].hp > 0) {
                        enemies[i].hp -= player_dmg;
                        break; }
            }
        }
    }


        enemies.erase(remove_if(enemies.begin(), enemies.end(), [](const Enemy& e){ return e.hp <= 0; }), enemies.end());
        if (enemies.empty()) break;


        last_enemy_actions.clear();
        for (auto& e : enemies) {
            int skutecne_poskozeni = apply_player_resistance(e.attack, p.resistance);
            p.hp -= skutecne_poskozeni;
            string akce = "Utocil za " + to_string(skutecne_poskozeni);
            last_enemy_actions.push_back(akce);
            cout << e.name << " utoci za " << skutecne_poskozeni << " poskozeni." << endl;
            if (p.hp < 0) p.hp = 0;
        }

        enemies.erase(remove_if(enemies.begin(), enemies.end(), [](const Enemy& e){ return e.hp <= 0; }), enemies.end());
        if (enemies.empty()) break;

        // --- Nepřátelé útočí ---
        last_enemy_actions.clear();
        for (auto& e : enemies) {
            int skutecne_poskozeni = apply_player_resistance(e.attack, p.resistance);
            p.hp -= skutecne_poskozeni;
            string akce = "Utocil za " + to_string(skutecne_poskozeni);
            last_enemy_actions.push_back(akce);
            cout << e.name << " utoci za " << skutecne_poskozeni << " poskozeni." << endl;
            if (p.hp < 0) p.hp = 0;
        }

        clear_and_wait(1200);
        round++;
    }
    if (p.hp <= 0) {
        cout << "Zemrel jsi. Konec hry." << endl;
        exit(0);
    }
    Reward reward = calculate_rewards(p, original_enemies);
    cout << "Vyhral jsi souboj! Ziskavas " << reward.exp << " EXP a " << reward.gold << " zlata." << endl;
    p.exp += reward.exp; p.gold += reward.gold;
    check_level_up(p);
}

// --- Finální boss: NENAVIDIMKOLOSTESTI ---
void nenavidimkolostesti_fight(Player& p) {
    string boss_name = "NENAVIDIMK0LOSTESTI";
    int boss_max_hp = 60;
    int boss_hp = 60;
    int boss_base_attack = 25;
    string last_player_action = "";
    string last_boss_action = "";
    int round = 0;
    while (p.hp > 0 && boss_hp > 0) {
        clear_and_wait(1200);
        clear();

        if (round > 0) {
            cout << "--- Akce minuleho kola ---" << endl;
            if (!last_player_action.empty())
                cout << "Hrac: " << last_player_action << endl;
            if (!last_boss_action.empty())
                cout << boss_name << ": " << last_boss_action << endl;
            cout << "--------------------------" << endl;
        }

        cout << "--------Souboj s bossem--------" << endl;
        print_player_stats(p);
        cout << boss_name << " | HP: " << boss_hp << "/" << boss_max_hp << endl;

        double boss_hp_percent = (double)boss_hp / boss_max_hp * 100.0;
        int dmg_mult;
        int resistance_boss = 0;
        bool half_reduction = false;
        if (boss_hp_percent > 80) {
            dmg_mult = 1; resistance_boss = 0;
        } else if (boss_hp_percent > 60) {
            dmg_mult = 2; resistance_boss = 1;
        } else if (boss_hp_percent > 40) {
            dmg_mult = 3; resistance_boss = 2;
        } else if (boss_hp_percent > 20) {
            dmg_mult = 4; resistance_boss = 3;
        } else {
            dmg_mult = 5; half_reduction = true;
        }

        print_abilities(p);
        int ability_choice = 1;
        cout << "Vyber schopnost (cislo): ";
        cin >> ability_choice;
        if (ability_choice < 1 || ability_choice > (int)p.abilities.size()) ability_choice = 1;
        Ability ab = p.abilities[ability_choice-1];

        int player_attack = ab.damage;
        last_player_action = ""; // reset

        if (ab.name == "Zabaci kop" || ab.name == "Skleneny uder" || ab.name == "Dlouhe mlaceni") {
            int dmg = roll_damage_with_ability(p.attack, ab.damage);
            player_attack = dmg;
            last_player_action = "Pouzil " + ab.name + " a hodil " + to_string(dmg) + " (kostka max " + to_string(p.attack) + " + ability " + to_string(ab.damage) + ")";
            cout << "Hodil jsi na utok: " << dmg << " (kostka max " << p.attack << " + ability " << ab.damage << ")" << endl;
        } else if (ab.name == "Oziveni") {
            if (p.hp < p.max_hp) {
                int heal_amt = 0;
                if (p.player_class == "konzolovy_uzivatel") heal_amt = 5;
                else if (p.player_class == "skleneny_kanon") heal_amt = 3;
                else if (p.player_class == "proc_ma_vsechno_tolik_hp") heal_amt = 2;
                p.hp += heal_amt;
                if (p.hp > p.max_hp) p.hp = p.max_hp;
                last_player_action = "Pouzil Oziveni a pridal si " + to_string(heal_amt) + " zivotu.";
                cout << "Pridal sis zivoty.\n";
            } else {
                last_player_action = "Zkousel Oziveni, ale mel plne zivoty.";
                cout << "Mas plne zivoty.\n";
            }
            player_attack = 0;
        } else if (ab.name == "Pouzit Bandaze") {
            if (p.hp < p.max_hp && p.heal > 0) {
                int healing = roll(12);
                last_player_action = "Pouzil bandaze a vylecil se o " + to_string(healing);
                cout << "Hodil jsi " << healing << " na leceni pomoci bandazi." << endl;
                if ((p.hp + healing) > p.max_hp) {
                    p.hp = p.max_hp;
                    cout << "Doplnil sis zivoty na maximum!" << endl;
                } else {
                    p.hp += healing;
                    cout << "Doplnil sis zivoty o " << healing << endl;
                }
                p.heal--;
            } else {
                last_player_action = "Zkousel pouzit bandaze, ale nemohl vylecit.";
                cout << "Bandaze nesly pouzit (mas plne HP nebo zadne bandaze)!" << endl;
            }
            player_attack = 0;
        } else {
            int dmg = roll_damage_with_ability(p.attack, ab.damage);
            player_attack = dmg;
            last_player_action = "Pouzil " + ab.name + " a hodil " + to_string(dmg) + " (kostka max " + to_string(p.attack) + " + ability " + to_string(ab.damage) + ")";
            cout << "Hodil jsi na utok: " << dmg << " (kostka max " << p.attack << " + ability " << ab.damage << ")" << endl;
        }

        // Odolnost bosse
        if (!half_reduction) {
            if (player_attack > resistance_boss) player_attack -= resistance_boss;
            else player_attack = 0;
        } else {
            player_attack = player_attack / 2;
        }
        boss_hp -= player_attack;
        if (boss_hp < 0) boss_hp = 0;
        cout << "Zasahujes " << boss_name << " za " << player_attack << " poskozeni!" << endl;
        if (boss_hp <= 0) break;

        // --- Bossův tah ---
        int boss_damage = boss_base_attack * dmg_mult;
        int skutecne_poskozeni = apply_player_resistance(boss_damage, p.resistance);
        last_boss_action = "Utocil silou " + to_string(skutecne_poskozeni) + ".";
        cout << boss_name << " utoci silou " << skutecne_poskozeni << "!" << endl;
        p.hp -= skutecne_poskozeni;
        if (p.hp < 0) p.hp = 0;

        double player_hp_percent = (double)p.hp / p.max_hp * 100.0;
        int heal = 0;
        if (player_hp_percent <= 5) heal = 30;
        else if (player_hp_percent <= 20) heal = 20;
        else if (player_hp_percent <= 40) heal = 15;
        else if (player_hp_percent <= 60) heal = 10;
        else if (player_hp_percent <= 80) heal = 5;
        else heal = 0;
        if (heal > 0) {
            boss_hp += heal;
            if (boss_hp > boss_max_hp) boss_hp = boss_max_hp;
            last_boss_action += " Uzdravil se o " + to_string(heal) + " HP!";
            cout << boss_name << " se uzdravuje o " << heal << " HP!" << endl;
        }

        if (p.hp <= 0) {
            cout << "Zemrel jsi. Konec hry." << endl;
            exit(0);
        }
        round++;
        clear_and_wait(2200);
    }
    if (p.hp > 0) {
        cout << endl << "Porazil jsi " << boss_name << "! Vyhral jsi hru!" << endl;
        clear_and_wait(3200);
    }
}

// --- Hlavní hra ---
int main() {
    srand(time(0));
    Player player;
    cout << "Vitej v textovem RPG. Zadej sve jmeno: ";
    cin >> player.name;
    class_selection(player);
    for (size_t i = 0; i < game_map.size(); ++i) {
        clear();
        cout << "Lokace: " << i+1 << "/" << game_map.size() << endl;
        print_player_stats(player);
        Encounter enc = game_map[i];
        if (enc.type == VILLAGE) {
            village(player, {enc.name});
        } else if (enc.type == ENEMY1 || enc.type == ENEMY2 || enc.type == ENEMY3) {
            vector<Enemy> enemies;
            for (int j = 0; j < enc.count; ++j)
                enemies.push_back(make_enemy(i+j));
            cout << "Souboj s " << enc.count << " monstry!" << endl;
            fight(player, enemies, false);
        } else if (enc.type == MINIBOSS) {
            cout << "Souboj s minibossem: " << enc.name << endl;
            fight(player, {make_enemy(i, true)}, true);
        } else if (enc.type == BOSS) {
            nenavidimkolostesti_fight(player);
            break;
        }
        clear_and_wait(1500);
    }
    cout << "Diky za hraní!" << endl;
    return 0;
}
