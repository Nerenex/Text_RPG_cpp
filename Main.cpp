#include <iostream>
#include <cstdlib>
/*Tato knihovna slouží k tomu abych mohl vymazat již nepotřebný text. Pomocí system("cls");*/
#include <windows.h>
/*Tato knihovna slouží k tomu abych mohl používat funkci Sleep a zpomalovat tak chod hry*/
#include <string>
#include <ctime>
#include <limits>

using namespace std;

/*gameplay variables*/
int strength, resistance, stamina, speed, hp, game_part, floor, attack;
string player_class;
string enemy;
/*gameplay field*/
int enemy_stats[5] = {3, 0, 0, 0, 0};
string player_ability[5] = {"cenichovka", };
/*gameplay function*/
void floor_change(){
    game_part++;
    floor++;
    cout << "----------Vitej na " << floor << ". patre----------";
}
    /*fight mechanics*/
void player_attack(int attack){
    cout << "pouzivas schopnost " << player_ability[attack-1] << endl;
}
    /*Tato funkce slouzis k provedeni schopnosti hrace*/
void fight_loop(){
    do{
        Sleep(1500);
        system("cls");
        /*FTUI*/
        cout << "--------probiha souboj--------" << endl
        << "class: " << player_class << endl
        << "sila: " << strength << " odolnost: " << resistance << " stamina: " << stamina << " rychlost: " << speed << endl
        << "HP " << hp << endl
        << "schopnosti: " << endl;
        for (int i = 0; i < 5; i++){
            if(player_ability[i] == ""){
                cout << i+1 << ". .........." << endl;
            }else{
            cout << i+1 << ". " << player_ability[i] << endl;
            }
        }
        /*FTEI*/
        cout << "bojujes proti: " << enemy << endl
        << "sila: " << enemy_stats[0] << " odolnost: " << enemy_stats[1] << " stamina: " << enemy_stats[2] << " rychlost: " << enemy_stats[3] << endl
        << "HP " << enemy_stats[4] << endl;
        /*Mechanika ktera rozhoduje kdo je rychlejsi*/
        if(speed >= enemy_stats[2]){
            cout << "jakou schopnost chces pouzit: ";
            cin >> attack;
            cout << endl;
            if(cin.fail()) {
                cout << "takovou schopnost neumime, promarnil si nasi sanci" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }else{
            player_attack(attack);
            }
        }else{
            cout << enemy << "je rychlejsi a utoci prvni" << endl; 
        }
    }while(hp != 0);
}
/*code function */
void vypravec_speak(string field, int phrase){
        cout << field[phrase] << endl;
}
/*voices variables*/
string schizo_voice_wi[5] = {
    "Hele na nerozhodnyho si muzes hrat jinde.",
    "Hele tebe ta rána do hlavy fakt ovlivnila? Nebo si takovej pořád?",
    "Hodláš dělat i něco co dává smysl, nebo to mám vzdát a nechat tě tu slepýho běhat světem.",
     "Mame jen ctyri mozne cesty, tak si jednu vyber a nevymyslej kraviny",
     "Vim ze sem z nás dvou ten chytrejsi, ale myslel jsem ze do ctyr pocitat umis."
   };
/*voices function*/
void voices(string phrase[], int size){
    int random = rand( ) % size;
    cout << phrase[random] << endl;
}

/*controls variables*/
int proces = 1;
int input_value;
string input;
/*controls function*/
void player_input(){
    do {
        input_value = 0;
        input = "";
        cout << "input:) : " << endl;
        cin >> input;

        if (input == "a"){
            input_value = 1;
            proces = 0;
        }else if(input == "b"){
            input_value = 2;
            proces = 0;
        }else if(input == "c"){
            input_value = 3;
            proces = 0;
        }else if(input == "d"){
            input_value = 4;
            proces = 0;
        }else{
            input_value = 0;
            proces = 1;
            voices(schizo_voice_wi, 5);
        }
    } while (proces == 1);
}

/*story variables*/
string player_name;
string a1 = "";
/*story function*/
void name(){
    char Y_N; 
    cout << "Vypadato ze mame amnesii a ocividne i schyzofrenii. Jak ze se to jmenujeme, nevzpominas si? " << endl;
    do{
    cin >> player_name;
    cout << "Ses si jisty? Y/N." << endl;
    cin >> Y_N;
    switch (Y_N)
    {
    case 'Y':
        proces = 0;
        break;
    case 'N':
        cout << "Jake je teda nase jmeno?" << endl;
        break;
    default:
        break;
    }
    }while(proces == 1);
    cout << "Nemam ten dojem ze je to nase jmeno, ale docasne si tak asi rikat muzem. Dobre od tedka sme " << player_name << endl << endl;
}
void class_selection(){
    cout << "Nepamatujes si co byla nase classa. Vim ze jsou tri classy, ale nemuzu si vpomenout co byla ta nase." << endl;

    cout << "classy:" << endl

    << "konzolovy_uzivatel: vetsinu her hrajes na konzily a proto by si nemusel zvladnout obtiznoust ostatnich class." << endl
    << "specifika teto classy:" << endl
    << "sila = 8" << endl
    << "odolnost = 8" << endl
    << "stamina = 3" << endl
    << "rychlost = 8" << endl
    << "hp = 80" << endl
    << endl
    << "skleneny_kanon: tvoje sila je obrovská, ale tvoje telo prekvapive krehke." << endl
    << "specifika teto classy:" << endl
    << "sila = 12" << endl
    << "odolnost = 2" << endl
    << "stamina = 1" << endl
    << "rychlost = 10" << endl
    << "hp = 25" << endl
    << endl
    << "proc_ma_vsechno_tolik_hp: i pitomého komára budes mlatit hodne dlouho" << endl
    << "specifika teto classy:" << endl
    << "sila = 3" << endl
    << "odolnost = 8" << endl
    << "stamina = 2" << endl
    << "rychlost = 5" << endl
    << "hp = 50" << endl
    << endl;
    proces = 1;
    do{
        cin >> player_class;
        if (player_class == "konzolovy_uzivatel"){
            strength = 8;
            resistance = 8;
            speed = 8;
            stamina = 3;
            hp = 80;
            cout << "Pockej ty si konzolista? Tohle bude bolest." << endl
            << "Zvolili jste classu: konzolovy_uzivatele" << endl;
            proces = 0;
        } else if (player_class == "skleneny_kanon"){
            strength = 12;
            resistance = 2;
            stamina = 1;
            speed = 10;
            hp = 25;
            cout << "Tady nekdo cetl One punch mana, ze jo?" << endl
            << "Zvolili jste classu: skleneny_kanon" << endl;
            proces = 0;
        } else if (player_class == "proc_ma_vsechno_tolik_hp"){
            strength = 3;
            resistance = 8;
            stamina = 2;
            speed = 5;
            hp = 50;
            cout << "Ty si masochista?" << endl
            << "Zvolili jste classu: proc_ma_vsechno_tolik_hp" << endl;
            proces = 0;
        } else {
            voices(schizo_voice_wi, 3);
        }
    }while(proces == 1);
}


/*actual hra*/
int main(){
    srand(time(0));
    /*
    cout << "Tak asi aby sme se dali nejak do pohybu. Vidim drevene dvere lehce, to je doslova vse jinak je vsude kolem jen bílo. Co jdeme delat?" << endl
         << "a: vejdeme do dveri" << endl
         << "b: vejdeme do dveri cool zpusobem" << endl
         << "c: otervreme dvere a pak vejdeme" << endl
         << "d: zustanem v bezpecne bile prazdnote a umreme na hlad" << endl;
    player_input();
    if (input != "d"){
        cout << "Sem rad ze si rozumime." << "Vchazime do dveri, dobrodruzstvi zacina." << endl;
        floor_change();
    */
   cout << "Vchazime do jeskyne kde na nas utoci kostlivec."  << endl;
   hp = 1;
   enemy = "kostlivec";
    fight_loop();
}