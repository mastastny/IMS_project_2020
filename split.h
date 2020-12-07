#ifndef IMS_PROJECT_2020_SPLIT_H
#define IMS_PROJECT_2020_SPLIT_H

#include "string"
#include "vector"
#include <algorithm>

using namespace std;

/**
 * Metoda, ktera upravi hodnoty s plovouci desetinnou carkou, ktere precte ze souboru, tak, aby byly pouzitelne s beznymi funkcemi jyzka C++.
 * @param number cislo ve formatu retezce
 * @return upravene cislo ve formatu retezce
 */

string preprocessFloat(string number);

/**
 * Metoda, ktera rozdeli retezec podle zadaneho delimiteru a ulozi tyto casti do vektoru
 * @param myStr retezec
 * @param delimeter rozdelovac
 * @return vraci vektor rozdelenych casti retezce
 */
vector<string> split(string myStr, string delimeter);

#endif //IMS_PROJECT_2020_SPLIT_H
