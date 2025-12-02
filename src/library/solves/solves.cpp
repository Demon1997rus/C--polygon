#include "solves.h"

#include <climits>

namespace rdi {

namespace {
constexpr int MOD = 1e9 + 7;
}

// medium level
vector<vector<int>> threeSum(vector<int> &nums)
{
    vector<vector<int>> ans;
    std::sort(nums.begin(), nums.end());
    const vector<int>::size_type n = nums.size();
    for (vector<int>::size_type i = 0; i < n; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            if (nums[i] + nums[left] + nums[right] == 0) {
                ans.push_back({nums[i], nums[left], nums[right]});
                ++left;
                while (left < right && nums[left] == nums[left - 1]) {
                    ++left;
                }
            } else if (nums[i] + nums[left] + nums[right] < 0) {
                ++left;
            } else {
                --right;
            }
        }
    }
    return ans;
}

// 121 - leetcode easy level
int maxProfit(vector<int> &prices)
{
    int ans = 0;
    int minIndex = 0;
    for (vector<int>::size_type i = 1; i < prices.size(); ++i) {
        if (prices[minIndex] > prices[i]) {
            minIndex = i;
        } else {
            ans = std::max(ans, prices[i] - prices[minIndex]);
        }
    }
    return ans;
}

// 2824 - leetcode easy level
int countPairs(vector<int> &nums, int target)
{
    int ans = 0;
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < (int) nums.size(); ++i) {
        for (int j = i + 1; j < (int) nums.size(); ++j) {
            if (i == j - 1 && nums[i] + nums[j] >= target) {
                break;
            }
            if (nums[i] + nums[j] < target) {
                ++ans;
            }
        }
    }
    return ans;
}

/*!
 * \brief isPalindrome - проверяет является ли строка палиндромом. easy level
 */
bool isPalindrome(string s)
{
    if (s.empty()) {
        return false;
    }
    string::size_type left = 0;
    string::size_type right = s.size() - 1;
    while (left < right) {
        while (left < right && !std::isalnum(s[left])) {
            ++left;
        }
        while (left < right && !std::isalnum(s[right])) {
            --right;
        }

        if (std::tolower(s[left]) != std::tolower(s[right])) {
            return false;
        }
        ++left;
        --right;
    }
    return true;
}

/*!
 * \brief reverseSentence - переворачивает предложение на месте. easy level
 *
 * Работает только с пробелами
 * Пример: "try again" -> "again try", "dimka work mars" -> "mars work dimka"
 */
void reverseSentence(string &sentence)
{
    std::reverse(sentence.begin(), sentence.end());
    string::size_type index = 0;
    for (string::size_type i = 1; i < sentence.size(); ++i) {
        if (std::isspace(sentence[i])) {
            std::reverse(sentence.begin() + index, sentence.begin() + i);
            index = i + 1;
            ++i;
        }
    }
    std::reverse(sentence.begin() + index, sentence.end());
}

/*!
 * \brief searchPair - определяет есть ли пара чисел в массиве, которая находится не более чем
 * на k индексов друг от друга и не различается не более чем на t по значению. medium level
 */
bool searchPair(vector<int> &nums, int k, int t)
{
    // corner-case
    if (nums.size() < 2 || k == 0) {
        return false;
    }

    const int n = nums.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < i + k && j < n; ++j) {
            if (abs(nums[i] - nums[j]) <= t) {
                return true;
            }
        }
    }
    return false;
}

void helperGenerateParenthesis(vector<string> &ans, string &combination, int open, int closed,
                               int n)
{
    // База рекурсии
    if ((open + closed) == (2 * n)) {
        ans.push_back(combination);
        return;
    }

    if (open < n) {
        combination.push_back('(');
        helperGenerateParenthesis(ans, combination, open + 1, closed, n);
        combination.pop_back();
    }

    if (closed < open) {
        combination.push_back(')');
        helperGenerateParenthesis(ans, combination, open, closed + 1, n);
        combination.pop_back();
    }
}

/*!
 * \brief generateParenthesis - Учитывая n пар круглых скобок, генерирует
 * все комбинаций хорошо сформированных круглых скобок. medium level
 */
vector<string> generateParenthesis(int n)
{
    vector<string> ans;
    string combination;
    helperGenerateParenthesis(ans, combination, 0, 0, n);
    return ans;
}

/*!
 * \brief sequentialNumbers - формирует отсортированный массив последовательных чисел в заданном
 * диапазоне. Последовательные числа - это где каждое число следущего ряда больше на единицу.
 * Пример: 12, 123, 234, 1234, 123456, 345, 456. medium level
 */
vector<int> sequentialNumbers(int low, int high)
{
    vector<int> ans;
    for (int startDigit = 1; startDigit < 9; ++startDigit) {
        int num = startDigit;
        for (int endDigit = startDigit + 1; endDigit < 10; ++endDigit) {
            num *= 10;
            num += endDigit;
            if (num >= low && num <= high) {
                ans.push_back(num);
            }
        }
    }
    std::sort(ans.begin(), ans.end());
    return ans;
}

/*!
 * \brief longestValidParentheses - Если строка содержит только символы '(' и ')', возвращает
 * длину самой длинной (хорошо сформированной) подстроки в круглых скобках - hard
 */
int longestValidParentheses(string s)
{
    if (s.empty()) {
        return 0;
    }
    const int n = s.size();
    vector<bool> matrix(n, false);
    stack<pair<char, int>> st;
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == '(') {
            st.push({c, i});
        } else {
            if (st.empty() || st.top().first != '(') {
                continue;
            }
            matrix[st.top().second] = true;
            matrix[i] = true;
            st.pop();
        }
    }

    int ans = 0;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (matrix[i]) {
            ++count;
        } else {
            count = 0;
        }
        ans = std::max(ans, count);
    }
    return ans;
}

/*!
 * \brief mergeKLists - Предоставляется массив из k списков связанных списков, каждый список
 *  связанных списков сортируется в порядке возрастания. Объедините все связанные списки в один
 *  отсортированный связанный список и верните его.
 * struct ListNode {
 *  int val;
 *  ListNode *next;
 *  ListNode() : val(0), next(nullptr) {}
 *  ListNode(int x) : val(x), next(nullptr) {}
 *  ListNode(int x, ListNode *next) : val(x), next(next) {}
 *  };
 */
ListNode *mergeKLists(vector<ListNode *> &lists)
{
    auto compare = [](ListNode *first, ListNode *second) { return first->val > second->val; };
    priority_queue<ListNode *, vector<ListNode *>, decltype(compare)> pq(compare);
    for (ListNode *list : lists) {
        if (list) {
            pq.push(list);
        }
    }
    ListNode head;
    ListNode *temp = &head;
    while (!pq.empty()) {
        ListNode *node = pq.top();
        pq.pop();
        if (node->next) {
            pq.push(node->next);
        }
        temp->next = new ListNode(node->val);
        temp = temp->next;
    }
    return head.next;
}

/*!
 * \brief isAnagram - вычисляет анаграмму
 */
bool isAnagram(const string &s1, const string &s2)
{
    int arr[26] = {0};
    for (char c : s1) {
        arr[c - 'a'] += 1;
    }

    for (char c : s2) {
        arr[c - 'a'] -= 1;
    }

    for (int counter : arr) {
        if (counter != 0) {
            return false;
        }
    }
    return true;
}

/*!
 * \brief groupAnagrams - Учитывая массив строк strs, сгруппируйте анаграммы вместе. Ответ можно
 * вернуть в любом порядке. Анаграмма - это слово или фраза, образованная перестановкой букв
 * другого слова или фразы, обычно с использованием всех исходных букв ровно один раз. medium
 * "eat", "tea", "tan", "ate", "nat", "bat"
 */
vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    vector<vector<string>> ans;
    unordered_map<string, vector<string>> sortAnagram;
    for (string &str : strs) {
        string key = str; // приходится копировать для сортировки
        std::sort(key.begin(), key.end());
        sortAnagram[key].push_back(std::move(str));
    }
    ans.reserve(sortAnagram.size());
    for (auto &p : sortAnagram) {
        ans.push_back(std::move(p.second));
    }
    return ans;
}

/*!
 * \brief isValidSudoku - Определите, действительна ли плата 9 x 9 Sudoku. Только заполненные
 * ячейки должны проверяться в соответствии со следующими правилами:
 * 1) Каждая строка должна содержать цифры 1-9 без повторения.
 * 2) Каждый столбец должен содержать цифры 1-9 без повторения.
 * 3) Каждая из девяти подпапок сетки 3 x 3 должна содержать цифры 1-9 без повторения.
 * Примечание: Доска Судоку (частично заполненная) может быть действительной, но не обязательно
 * разрешимой. Только заполненные ячейки должны быть проверены в соответствии с указанными
 * правилами.
 */
bool isValidSudoku(vector<vector<char>> &board)
{
    // Отвечает на вопрос существует ли такая цифра в такой то строке
    vector<vector<bool>> rows(9, vector<bool>(9, false));

    // Отвечает на вопрос существует ли такая цифра в такой то колонке
    vector<vector<bool>> cols(9, vector<bool>(9, false));

    // Отвечает на вопрос существует ли такая цифра в таком то квадрате
    vector<vector<bool>> subs(9, vector<bool>(9, false));

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            char c = board[row][col];
            if (c == '.') {
                continue;
            }
            int num = c - '0' - 1; // вычисляем цифру для индекса
            int sub = (row / 3) * 3 + col / 3; // номер квадрата
            if (rows[row][num] || cols[col][num] || subs[sub][num]) {
                return false;
            }
            rows[row][num] = true;
            cols[col][num] = true;
            subs[sub][num] = true;
        }
    }
    return true;
}

/*!
 * \brief rotate - Вы получили двумерную матрицу n x n, представляющую изображение, поверните
 * изображение на 90 градусов (по часовой стрелке). Необходимо повернуть изображение по месту,
 * что означает непосредственное изменение входной 2D матрицы. НЕ ВЫДЕЛЯЙТЕ другую двумерную
 * матрицу и выполняйте поворот.
 */
void rotateReverse(vector<vector<int>> &matrix)
{
    // solve reverse trick
    // time complexity - O(n^2)
    // memory complexity - O(1)
    const int n = (int) matrix.size();
    std::reverse(matrix.begin(), matrix.end());
    for (int row = 0; row < n; ++row) {
        for (int col = row + 1; col < n; ++col) {
            std::swap(matrix[row][col], matrix[col][row]);
        }
    }
}

/*!
 * \brief compressedString - Нужно сжать строку AAAABBBCCCD -> A4B3C3D
 * Если буква то одна то цифру ставить не нужно
 */
string compressedString(const string &str)
{
    using TypeSolve = string::size_type;
    const TypeSolve n = str.size();
    string ans;
    TypeSolve counter = 1;
    for (TypeSolve i = 0; i < n; ++i) {
        if (i + 1 >= n || str[i] != str[i + 1]) {
            if (counter == 1) {
                ans += str[i];
            } else {
                ans += str[i];
                ans += to_string(counter);
                counter = 1;
            }
        } else {
            ++counter;
        }
    }
    return ans;
}

/*!
 * \brief findCustomSubstr - Нужно найти существует ли такая подстрока target в строке str после
 * перестановки букв в строке str
 * ("rbeeok","bee") перестановка -> ("reebok", "bee") -> ответ индекс 1, если нет правильного
 * ответа то возращаем -1
 */
int findCustomSubstr(string str, string target)
{
    using TypeSolve = string::size_type;
    if (str.size() < target.size()) {
        return -1;
    }

    unordered_map<char, int> charCounter;
    for (char c : target) {
        charCounter[c] += 1;
    }
    // b -> 1
    // e -> 2

    TypeSolve n = str.size();    // Размер str
    TypeSolve k = target.size(); // Размер target
    TypeSolve index = 0;         // Индекс в строке str
    int nonZeroSize = charCounter.size(); // количество уникальных переменных в строке target

    // Сначала нужно проитерировать окно в str
    // |ree|bok
    // после цикла получим следующий результат
    // e -> 0
    // r -> -1
    // b -> 1
    // nonZeroSize -> 2
    while (index < k) {
        char c = str[index];
        int &value = charCounter[c];
        value -= 1;
        if (value == 0) {
            --nonZeroSize;
        } else if (value == -1) {
            ++nonZeroSize;
        }
        ++index;
    }

    // тут обязательно нужно проверить является ли target подстрокой окошка в str
    // если да то просто возращаем ноль в качестве индекса
    if (nonZeroSize == 0) {
        return 0;
    }

    // Далее чуть сложнее r|eeb|ok окошко eeb
    // нам нужно выкинуть символ r и обработать символ b, то есть мы двигаем окошко вперед по
    // строке
    // 1) когда добавляем новый символ то логика сохраняется мы просто вычитаем 1 c
    // нового символа и проверяем если он равен нулю то вычитываем единицу из количества
    // уникальных символов, если случилась ситуация что он ушел в -1 то значит прибавляем
    // единицу
    // 2) ситуация когда мы выкидываем символ r с окна, тут все просто вместо того чтобы
    // отнимать единицу, мы прибавляем единицу. и проверяем аналогично обратным правилам которые
    // я описал в 1 пункте
    // 3) в конце каждого цикла мы проверям нашу переменную nonZeroSize если она стала равным
    // нулю то возращаем index - k + 1
    while (index < n) {
        char c = str[index];
        int &value = charCounter[c];
        value -= 1;
        if (value == 0) {
            --nonZeroSize;
        } else if (value == -1) {
            ++nonZeroSize;
        }

        c = str[index - k];
        value = charCounter[c];
        value += 1;
        if (value == 0) {
            --nonZeroSize;
        } else if (value == 1) {
            ++nonZeroSize;
        }
        if (nonZeroSize == 0) {
            return index - k + 1;
        }
        ++index;
    }
    return -1;
}

/*!
 * \brief lengthOfLastWord - При наличии строки s, состоящей из слов и пробелов, возвращает
 * длину последнего слова в строке.
 * Слово - это максимум подстрока состоит только из символов, не являющихся пробелами.
 */
int lengthOfLastWord(string s)
{
    string::size_type counter = 0;
    string::size_type index = s.size() - 1;
    while (index != string::npos && std::isspace(s[index])) {
        --index;
    }
    while (index != string::npos && !std::isspace(s[index])) {
        ++counter;
        --index;
    }
    return counter;
}

/*!
 * \brief removeElement - Если задано целое число массива и целое значение val, удалите все
 * вхождения val в числах на месте. Порядок элементов может быть изменен. Затем возвращает число
 * элементов в числах, которые не равны val.
 *
 * Рассмотрим число элементов в числах, которые не равны val быть k, чтобы получить принято, вы
 * должны сделать следующие вещи:
 *
 * Измените номера массива так, чтобы первые k элементов чисел содержали элементы, не равные
 * val. Остальные элементы чисел не важны, как и размер чисел. Возврат k.
 */
int removeElement(vector<int> &nums, int target)
{
    typedef vector<int>::size_type TypeSolve;
    const TypeSolve size = nums.size();
    TypeSolve insertIndex = 0;
    TypeSolve currentIndex = 0;
    while (currentIndex < size) {
        if (nums[currentIndex] != target) {
            nums[insertIndex] = nums[currentIndex];
            ++insertIndex;
        }
        ++currentIndex;
    }
    return insertIndex;
}

/*!
 * \brief majorityElement - Возвращайте мажоритарный элемент, если задано число массива размером
 * n. Мажоритарный элемент - это элемент, который появляется более [n/2] раз. Можно
 * предположить, что мажоритарный элемент всегда существует в массиве.
 *
 * Ограничения:
 * n == nums.length
 * 1 <= n <= 5 * 10^4
 * -10^9 <= числа [i] <= 10^9
 *
 * Продолжение: Не могли бы вы решить проблему за линейное время и в O(1) пространстве?
 */
int majorityElement(vector<int> &nums)
{
    const int n = (int) nums.size();
    int counter = 1;
    int current = nums[0];
    for (int i = 1; i < n; ++i) {
        if (nums[i] == current) {
            ++counter;
        } else {
            if (counter == 1) {
                current = nums[i];
            } else {
                --counter;
            }
        }
    }
    return current;
}

ListNode *helperDeleteDuplicates(ListNode *node)
{
    while (node && node->next && node->val == node->next->val) {
        node = node->next;
    }
    return node->next;
}

/*!
 * \brief deleteDuplicates - Учитывая заголовок отсортированного связанного списка, удалите все
 * узлы с повторяющимися номерами, оставив только отдельные номера из исходного списка. Также
 * можно вернуть отсортированный связанный список.
 *
 * Пример - (1->2->3->3->4->4->5) -> (1->2->5)
 * Пример - (1->1->1) -> (-)
 * Пример - (1->1->2) -> (2)
 *
 * Ограничения:
 *
 * Число узлов в списке находится в диапазоне [0, 300].
 * -100 <= Node.val <= 100
 * Список гарантированно сортируется в порядке возрастания.
 *
 * Solve two pointers
 * Time complexity - O(n)
 * Space complexity - O(1)
 */
ListNode *deleteDuplicates(ListNode *head)
{
    ListNode *slow = nullptr;
    ListNode *fast = head;
    while (fast && fast->next) {
        if (fast->val == fast->next->val) {
            fast = helperDeleteDuplicates(fast);
            slow ? slow->next = fast : head = fast;
        } else {
            slow = fast;
            fast = fast->next;
        }
    }
    return head;
}

/*!
 * \brief rearrangeArray - Даётся 0-индексный целый массив чисел чётной длины, состоящий из
 * равного числа положительных и отрицательных целых чисел. Необходимо переупорядочить элементы
 * чисел таким образом, чтобы измененный массив следовал заданным условиям: Каждая
 * последовательная пара целых чисел имеют противоположные знаки. Для всех целых чисел с
 * одинаковым знаком сохраняется порядок, в котором они присутствовали в нумах. Реорганизованный
 * массив начинается с положительного целого числа. Возврат измененного массива после
 * перегруппировки элементов в соответствии с вышеупомянутыми условиями.
 *
 * Пример 1:
 * Вход: числа = [3,1, -2, -5,2, -4]
 * Выход: [3, -2,1, -5,2, -4]
 * Объяснение:
 * Положительные целые числа в числах равны [3,1,2]. Отрицательные целые числа равны [-2, -5,
 * -4]. Единственным возможным способом переупорядочить их так, чтобы они удовлетворяли всем
 * условиям, является [3, -2,1, -5,2, -4]. Другие способы, такие как [1, -2,2, -5,3, -4],
 * [3,1,2, -2, -5, -4], [-2,3, -5,1, -4,2], неверны, поскольку они не удовлетворяют одному или
 * нескольким условиям.
 *
 * Пример 2: Вход: числа = [-1,1] Вывод: [1, -1]
 * Объяснение:
 * 1 - единственное положительное целое число, а -1 - единственное отрицательное целое число в
 * числах. Так числа переставляются в [1, -1].
 *
 * Ограничения:
 * 1) 2 <= nums.length <= 2 * 10^5
 * 2) nums.length является четным
 * 3) 1 < = | nums [i] | < = 10^5
 * 4) Числа состоят из равного числа положительных и отрицательных целых чисел.
 *
 * Solution:
 * time complexity: O(n)
 * space complexity: O(n)
 */
vector<int> rearrangeArray(vector<int> &nums)
{
    typedef vector<int>::size_type TypeSolve;
    const TypeSolve n = nums.size();
    vector<int> ans(n);
    TypeSolve positive = 0;
    TypeSolve negative = 1;
    TypeSolve i = 0;
    while (i < n) {
        if (nums[i] >= 0) {
            ans[positive] = nums[i];
            positive += 2;
        } else {
            ans[negative] = nums[i];
            negative += 2;
        }
        ++i;
    }
    return ans;
}

/*!
 * \brief largestPerimeter - Вы даете массив положительных чисел чисел длиной n.
 * Многоугольник - это фигура замкнутой плоскости, имеющая не менее 3 сторон. Самая длинная
 * сторона многоугольника меньше суммы других его сторон.
 * И наоборот, если у вас есть k (k >= 3) положительных вещественных
 * чисел a1, a2, a3,..., ak где a1 < = a2 < = a3 < =... < = ak и a1 + a2
 * + a3 +... + ak-1 > ak, то всегда существует многоугольник с k сторонами, длины которых a1,
 * a2, a3,..., ak. Периметр многоугольника представляет собой сумму длин его сторон. Возвращает
 * наибольший возможный периметр многоугольника, стороны которого могут быть образованы из
 * чисел, или -1, если невозможно создать многоугольник.
 */
long long largestPerimeter(vector<int> &nums)
{
    return -1;
}

/*!
 * \brief findLeastNumOfUniqueInts - Задается массив целых чисел arr и целое число k. Найдите
 * наименьшее количество уникальных целых чисел после удаления ровно k элементов.
 *
 * Пример 1:
 * Вход: arr = [5,5,4], k = 1
 * Вывод: 1
 * Пояснение: Удалите один 4, осталось только 5.
 *
 * Пример 2:
 * Вход: arr = [4,3,1,1,3,3,2], k = 3
 * Вывод: 2
 * Пояснение: Удалите 4, 2 и либо одну из двух 1s, либо три 3s. 1 и 3 будут оставлены.
 *
 * Ограничения:
 * 1 <= arr.length <= 10^5
 * 1 <= arr [i] <= 10^9
 * 0 <= k <= arr.length
 */
int findLeastNumOfUniqueInts(vector<int> &arr, int k)
{
    unordered_map<int, int> arrCounter;
    for (int num : arr) {
        arrCounter[num] += 1;
    }
    priority_queue<int, vector<int>, std::greater<int>> pq;
    for (auto &counter : arrCounter) {
        pq.push(counter.second);
    }
    while (!pq.empty()) {
        k -= pq.top();
        pq.pop();
        if (k < 0) {
            return pq.size() + 1;
        }
    }
    return 0;
}

/*!
 * \brief lengthOfLongestSubstring - При наличии строки s найдите длину самой длинной подстроки
 * без повторения символов.
 *
 *
 * Пример 1:
 * Вход: s = «abcabcbb»
 * Выходные данные: 3
 * Объяснение: Ответ «abc», длиной 3.
 *
 * Пример 2:
 * Вход: s = «bbbb»
 * Вывод: 1
 * Объяснение: Ответ «b», длиной 1.
 *
 * Пример 3:
 * Вход: s = «pwwkew»
 * Выходные данные: 3
 * Объяснение: Ответ «wke», длиной 3.
 * Обратите внимание, что ответ должен быть подстрокой, «pwke» - подпоследовательность, а не
 * подстрока.
 *
 * Ограничения:
 * 0 < = s.length < = 5 * 10^4
 * s состоит из английских букв, цифр, символов и пробелов.
 */
int lengthOfLongestSubstring(string s)
{
    using TypeSolve = string::size_type;
    if (s.empty()) {
        return 0;
    }
    unordered_set<char> uniqueChar;
    TypeSolve start = 0, end = 0, ans = 0, n = s.size();

    while (end < n) {
        if (uniqueChar.insert(s[end]).second) {
            ++end;
            ans = std::max(ans, uniqueChar.size());
        } else {
            uniqueChar.erase(s[start]);
            ++start;
        }
    }
    return (int) ans;
}

/*!
 * \brief maximumOddBinaryNumber - Вы получили двоичную строку s, которая содержит по крайней
 * мере один «» 1 «». Необходимо переупорядочить биты таким образом, чтобы полученное двоичное
 * число было максимальным нечетным двоичным числом, которое может быть создано из этой
 * комбинации.
 * Возвращает строку, представляющую максимальное нечетное двоичное число, которое может быть
 * создано из данной комбинации. Обратите внимание, что результирующая строка может иметь
 * начальные
 * нули.

 * Пример 1:
 * Вход: s = «010»
 * Вывод: «001»
 * Объяснение: Поскольку есть только один '1', он должен быть в последней позиции. Так что ответ
 * «001».

 * Пример 2:
 * Вход: s = «0101»
 * Вывод: «1001»
 * Объяснение: Одна из '1' должен находиться в последней позиции. Максимальное число, которое
 * может
 * быть выполнено с оставшимися цифрами - «100». Так что ответ - «1001».

 * Ограничения:
 * 1 <= s.length <= 100
 * s состоит только из «0» и «1».
 * s содержит по крайней мере один «1».
 */
string maximumOddBinaryNumber(string s)
{
    int num = stoi(s, nullptr, 2);
    cout << "Num = " << num << endl;

    return string();
}

/*!
 * \brief removeZeroSumSubLists - Учитывая заголовок связанного списка, мы многократно удаляем
 * последовательные последовательности узлов, которые суммируются до 0, пока таких
 * последовательностей не будет. После этого верните заголовок окончательного связанного списка.
 * Вы можете вернуть любой такой ответ.
 *
 * (Обратите внимание, что в приведенных ниже примерах все последовательности являются
 * сериализацией объектов ListNode.)
 *
 * Пример 1:
 * Вход: head = [1,2, -3,3,1]
 * Вывод: [3,1]
 * Примечание: Ответ [1,2,1] также будет принят.
 *
 * Пример 2:
 * Вход: head = [1,2,3, -3,4]
 * Выходные данные: [1,2,4]
 *
 * Пример 3:
 * Вход: head = [1,2,3, -3, -2]
 * Вывод: [1]
 *
 * Ограничения:
 * Данный связанный список будет содержать от 1 до 1000 узлов.
 * Каждый узел в списке связей имеет -1000 <= node.val <= 1000.
 */
ListNode *removeZeroSumSubLists(ListNode *head)
{
    // memory O(1) - решение получится time O(n^3), так что это не вариант
    // Само задание похоже на нахождение подмассивов целочисленных значений в сумме составляющие
    // число target, там в лучшем решение используется хэш таблица(unordered_map), скорее всего
    // и тут тоже(нужно только подстроить само решение)
    return nullptr;
}

/*!
 * \brief productExceptSelf - Учитывая целое число массива, возвращайте ответ массива таким
 * образом, чтобы ответ [i] был равен произведению всех элементов чисел, кроме чисел [i].
 * Произведение любого префикса или суффикса чисел гарантированно помещается в 32-битное целое
 * число. Необходимо написать алгоритм, который выполняется за O (n) раз и без использования
 * операции деления.
 *
 * Example 1:
 * Input: nums = [1,2,3,4]
 * Output: [24,12,8,6]
 *
 * Input: nums = [-1,1,0,-3,3]
 * Output: [0,0,9,0,0]
 *
 * Ограничения:
 * 2 <= nums.length <= 105
 * -30 < = числа [i] < = 30
 * Произведение любого префикса или суффикса чисел гарантированно помещается в 32-битное целое
 * число.
 *
 * Продолжение: Можете ли вы решить проблему в O (1) дополнительной сложности пространства?
 * (Выходной массив не считается дополнительным пространством для анализа сложности
 * пространства.)
 */
vector<int> productExceptSelf(vector<int> &nums)
{
    if (nums.empty()) {
        return {};
    }
    const vector<int>::size_type n = nums.size();
    vector<int> product(n);

    product[0] = 1;
    for (int i = 1; i < (int) n; ++i) {
        product[i] = nums[i - 1] * product[i - 1];
    }

    int suffixProduct = 1;
    for (int i = n - 1; i >= 0; --i) {
        product[i] *= suffixProduct;
        suffixProduct *= nums[i];
    }

    return product;
}

/*!
 * \brief findMinArrowShots - Есть несколько сферических шариков, прикрепленных к плоской стене,
 * которая представляет XY-плоскость. Номера позиций представлены в виде двумерного целого
 * массива точек, где points[i] = [xstart, xend] обозначает номер позиции, горизонтальный
 * диаметр которого растягивается между xstart и xend. Вы не знаете точных координат y шариков.
 * Стрелки можно снимать прямо вертикально (в положительном направлении y) из разных точек вдоль
 * оси X. Шарик с xstart и xend разрывается стрелкой при x, если xstart < = x < = xend.
 * Количество стрелок, которые могут быть сняты, не ограничено. Стреляная стрела продолжает
 * бесконечно двигаться вверх, разрывая любые шарики на своем пути. Возвращайте минимальное
 * количество стрелок, которые должны быть сняты, чтобы разорвать все номера позиций. 452 medium
 * Пример 1:
 * Ввод: points = [[10,16], [2,8], [1,6], [7,12]]
 * Вывод: 2
 * Объяснение: Номера позиций могут быть разбиты на 2 стрелки:
 * - Стрелять стрелкой при x = 6, лопая шарики [2,8] и [1,6].
 * - Стрелять стрелкой при x = 11, лопнув шарики [10,16] и [7,12].
 *
 * Пример 2:
 * Ввод: points = [[1,2], [3,4], [5,6], [7,8]]
 * Выход: 4
 * Объяснение: Одну стрелку нужно снять для каждого шарика в общей сложности 4 стрелки.
 *
 * Пример 3:
 * Ввод: points = [[1,2], [2,3], [3,4], [4,5]]
 * Вывод: 2
 * Объяснение: Номера позиций могут быть разбиты на 2 стрелки:
 * - Стрелять стрелкой при x = 2, лопая шарики [1,2] и [2,3].
 * - Стрелять стрелкой при x = 4, разрывая шарики [3,4] и [4,5].
 *
 * Ограничения:
 * 1 < = points.length < = 10^5
 * points[i].length == 2
 * -2^31 < = points[i][0] < points[i][1] < = 2^31 - 1
 */
int findMinArrowShots(vector<vector<int>> &points)
{
    if (points.empty()) {
        return 0;
    }
    std::sort(points.begin(), points.end());
    vector<vector<int>> intervals;
    intervals.push_back(std::move(points[0]));
    for (int i = 1; i < (int) points.size(); ++i) {
        if (intervals.back()[1] >= points[i][0]) {
            intervals.back()[0] = std::max(intervals.back()[0], points[i][0]);
            intervals.back()[1] = std::min(intervals.back()[1], points[i][1]);
        } else {
            intervals.push_back(std::move(points[i]));
        }
    }
    return intervals.size();
}

/*!
 * \brief leastInterval - Предоставляется массив задач CPU, каждая из которых представлена
 * буквами от A до Z, и время охлаждения. Каждый цикл или интервал позволяет выполнить одну
 * задачу. Задачи могут быть выполнены в любом порядке, но существует ограничение: идентичные
 * задачи должны быть разделены по крайней мере n интервалами из-за времени охлаждения.
 * Возвращает минимальное количество интервалов, необходимых для выполнения всех задач.
 *
 * Пример 1:
 * Вход: tasks = [«A», «A», «A», «B», «B», «B»], n = 2
 * Выход: 8
 * Объяснение: Возможная последовательность: A - > B - > idle - > A - > B - > idle - > A - > B.
 * После выполнения задачи A необходимо подождать два цикла, прежде чем выполнять операцию A. То
 * же самое относится и к задаче B. В 3-м интервале ни A, ни B не могут быть выполнены, поэтому
 * вы свободны. К 4-му циклу можно снова сделать А по мере прохождения 2 интервалов.
 *
 * Пример 2:
 * Вход: tasks = [«A», «C», «A», «B», «D», «B»], n = 1
 * Выходные данные: 6
 * Объяснение: Возможная последовательность: A->B->A->B->C->D.
 * С интервалом охлаждения 1 можно повторить задачу только после другой задачи.
 *
 * Пример 3:
 * Вход: tasks = [«A», «A», «A», «B», «B», «B»], n = 3
 * Выход: 10
 * Объяснение: Возможная последовательность: A - > B - > idle - > idle - > A - > B - > idle - >
 * idle - > A - > B. Существует только два типа задач, A и B, которые должны быть разделены 3
 * интервалами. Это приводит к двойному простою между повторениями этих задач.
 *
 * Пример 4:
 * Вход: tasks = ['A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G'], n = 1
 * Выход: 12
 * Объяснение: A->B->A->C->A->D->A->E->A->F->A->G
 *
 * Ограничения:
 * 1 < = tasks.length <= 10^4
 * tasks[i] - прописное английское письмо.
 * 0 < = n <= 100
 */
int leastInterval(const vector<char> &tasks, int n)
{
    // Докажем что нибудь из условий задачи.
    // 1) Ответ не может быть меньше чем длина исходного массива tasks.

    // 2) Представим, что есть задача X количества count
    // - ответ не может быть больше, чем: X (n) X (n) X (n) X -> (count - 1) * (n + 1) + 1

    // 3) Если есть несколько задач с одинаковым (максимальным) количеством.
    // A-5 B-5 C-3 -> AB?AB?AB?AB?AB -> (count - 1) * (n + 1) + nMaxCount.
    // nMaxCount - количество букв с максимальной частотой.

    // 4) Из выше перечисленного докажем, что max(tasks.size(), (count - 1) * (n + 1) +
    // maxCount)
    // - является ответом
    // Конструктивный способ заполнения.
    // Двумерная диаграмма - по горизонтали - номер столбца - номер группы из n + 1 элемента.
    // По вертикали - n + 1 строка, сверху вниз - элементы группы

    // 5) Алгоритм: будем заполнять буквами по "строчкам" в порядке
    // A-5 B-5 C-3 | n = 2
    // A A A A A
    // B B B B B
    // C C C .

    // A-5 B-5 C-3 D-3 E - 2| n = 3
    // A A A A A
    // B B B B B
    // C C C E
    // D D D E
    int taskCounter[26] = {0};
    int maxCount = 0, nMaxCount = 0;
    for (char task : tasks) {
        int counter = (++taskCounter[task - 'A']);
        if (counter > maxCount) {
            maxCount = counter;
            nMaxCount = 1;
        } else if (counter == maxCount) {
            ++nMaxCount;
        }
    }
    return std::max(static_cast<int>(tasks.size()), (maxCount - 1) * (n + 1) + nMaxCount);
}

/*!
 * \brief mergeInBeetween - Имеются два связанных списка: list 1 и list 2 размеров n и m
 * соответственно. Удалите узлы list1 из узла ath в узел bth и поместите вместо них узел list2.
 *
 * Пример 1:
 * Вход: list1 = [10,1,13,6,9,5], = 3, b = 4, list2 = [1000000,1000001,1000002]
 * Вывод: [10,1,13,1000000,1000001,1000002,5]
 * Объяснение: Мы удаляем узлы 3 и 4 и ставим весь список2 на их место.
 *
 * Пример 2:
 * Вход: list1 = [0,1,2,3,4,5,6], = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
 * Вывод: [0 1 1000000 1000001 1000002 1000003 1000004 6]
 *
 * Ограничения:
 * 3 <= list1.length <= 10^4
 * 1 < = a <= b < list1.length - 1
 * 1 <= list2.length <= 10^4
 */
ListNode *mergeInBeetween(ListNode *list1, int a, int b, ListNode *list2)
{
    ListNode *slow = list1;
    ListNode *fast = list1;
    int counter = 0;
    while (counter < a - 1 && slow && fast) {
        slow = slow->next;
        fast = fast->next;
        ++counter;
    }

    while (counter < b && fast) {
        fast = fast->next;
        ++counter;
    }
    slow->next = list2;
    while (slow && slow->next) {
        slow = slow->next;
    }
    slow->next = fast->next;
    return list1;
}

/*!
 * \brief isPalindrome - Учитывая заголовок отдельно связанного списка, возвращайте значение
 * true, если это палиндром или false в противном случае. Задача 234 easy Leetcode
 *
 * Пример 1:
 * Ввод: head = [1,2,2,1]
 * Вывод: true
 *
 * Пример 2:
 * Вход: head = [1,2]
 * Вывод: false
 *
 * Ограничения:
 * Число узлов в списке находится в диапазоне [1, 10^5].
 * 0 <= Node.val <= 9
 *
 * Продолжение: Не могли бы вы сделать это за O(n) время и O(1) пространство?
 *
 * Time - O(n), Memory O(1)
 */
bool isPalindrome(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;
    ListNode *prev = nullptr;
    while (fast && fast->next) {
        ListNode *temp = slow;
        slow = slow->next;
        fast = fast->next->next;
        temp->next = prev;
        prev = temp;
    }
    if (fast) {
        slow = slow->next;
    }

    while (prev && slow) {
        if (prev->val != slow->val) {
            return false;
        }
        prev = prev->next;
        slow = slow->next;
    }
    return true;
}

/*!
 * \brief maxDepth - Строка является допустимой строкой в скобках (обозначаемой как VPS), если
 * она отвечает одному из следующих условий: Это пустая строка «» или одиночный символ, не
 * равный «(» или «)», Она может быть записана как AB (A, сцепленный с B), где A и B являются
 * VPS, или Он может быть записан как (A), где A является VPS. Мы также можем определить глубину
 * вложенности (S) любой VPS S следующим образом: depth («») = 0 depth (C) = 0, где C - строка с
 * одним символом, не равным «(» или «)». глубина (A + B) = max (глубина (A), глубина (B)), где
 * A и B являются VPS. depth («(» + A + «)») = 1 + depth (A), где A - VPS. Например, "", () ()
 * "и" () (()
 * ()) "являются VPS (с глубинами вложенности 0, 1 и 2), а") ("и" (() "не являются VPS. Если VPS
 * представлен в виде строки s, возвращает глубину вложенности s.
 *
 * Пример 1:
 * Вход: s = «(1 + (2 * 3) + ((8)/4)) + 1»
 * Выходные данные: 3
 * Объяснение: Цифра 8 находится внутри 3 вложенных скобок в строке.
 *
 * Пример 2:
 * Вход: s = «(1) + ((2)) + (((3)))»
 * Выходные данные: 3
 *
 * Ограничения:
 * 1 < = s.length < = 100 s состоит из цифр 0-9 и символов «+», «-», «*», «/», «(» и «)».
 * Гарантируется, что выражение s в скобках является VPS.
 */
int maxDepth(string s)
{
    int ans = 0;
    int currentMax = 0;
    for (char c : s) {
        if (c == '(') {
            ans = std::max(++currentMax, ans);
        } else if (c == ')') {
            --currentMax;
        }
    }
    return ans;
}

void numIslandsHelper(int row, int col, vector<vector<char>> &grid,
                      vector<vector<bool>> &matrix)
{
    if (row < 0 || row >= (int) grid.size() || col < 0 || col >= (int) grid[0].size() ||
        grid[row][col] == '0' || matrix[row][col]) {
        return;
    }
    matrix[row][col] = true;
    numIslandsHelper(row + 1, col, grid, matrix);
    numIslandsHelper(row - 1, col, grid, matrix);
    numIslandsHelper(row, col + 1, grid, matrix);
    numIslandsHelper(row, col - 1, grid, matrix);
}

/*!
 * \brief numIslands - Учитывая двумерную двоичную сетку, которая представляет карту «1» (земля)
 * и «0» (вода), возвращаем количество островов. Остров окружён водой и образован путём
 * соединения прилегающих земель горизонтально или вертикально. Можно предположить, что все
 * четыре края сетки окружены водой.
 *
 * Пример 1:
 * Вход: grid = [
 * ["1","1","1","1","0"],
 * ["1","1","0","1","0"],
 * ["1","1","0","0","0"],
 * ["0","0","0","0","0"]
 * ]
 * Вывод: 1
 *
 * Пример 2:
 * Вход: grid = [
 * ["1","1","0","0","0"],
 * ["1","1","0","0","0"],
 * ["0","0","1","0","0"],
 * ["0","0","0","1","1"]
 * ]
 * Выходные данные: 3
 *
 * Ограничения:
 * m == grid.length n == grid[i].length
 * 1 <= m, n <= 300 grid[i][j] равно «0» или «1».
 */
int numIslands(vector<vector<char>> &grid)
{
    int ans = 0;
    const vector<int>::size_type rows = grid.size();
    const vector<int>::size_type cols = grid[0].size();

    vector<vector<bool>> matrix(rows, vector<bool>(cols, false));
    for (vector<int>::size_type row = 0; row < rows; ++row) {
        for (vector<int>::size_type col = 0; col < cols; ++col) {
            // Если ячейка не использована и это земля
            if (!matrix[row][col] && grid[row][col] == '1') {
                ++ans;
                numIslandsHelper(row, col, grid, matrix);
            }
        }
    }

    return ans;
}

/*!
 * \brief findMaxK - Учитывая целочисленные числа массива, которые не содержат нулей, найдите
 * наибольшее положительное целое число k, так что -k также существует в массиве. Возвращает
 * положительное целое число k. Если такого целого числа нет, возвращает -1.
 *
 * Пример 1:
 * Вход: числа = [-1,2, -3,3]
 * Выходные данные: 3
 * Объяснение: 3 - единственный допустимый k, который мы можем найти в массиве.
 * Пример 2:
 * Вход: числа = [-1,10,6,7, -7,1]
 * Выход: 7
 * Объяснение: И 1, и 7 имеют свои соответствующие отрицательные значения в массиве. 7 имеет
 * большее значение. Пример 3: Вход: числа = [-10,8,6,7, -2, -3] Вывод: -1 Объяснение: Нет ни
 * одного действительного k, мы возвращаем -1.
 *
 * Ограничения:
 * 1 <= nums.length <= 1000
 * -1000 <= nums[i] <= 1000
 * nums[i] != 0
 */
int findMaxK(vector<int> &nums)
{
    std::sort(nums.begin(), nums.end());
    int left = 0;
    int right = nums.size() - 1;
    while (left < right && nums[left] < 0 && nums[right] > 0) {
        int leftNum = -nums[left];
        int rightNum = nums[right];
        if (leftNum > rightNum) {
            ++left;
        } else if (leftNum < rightNum) {
            --right;
        } else {
            return leftNum;
        }
    }
    return -1;
}

/*!
 * \brief removeNodes - Вам предоставляется заголовок связанного списка.
 * Удалите каждый узел, который имеет узел с большим значением в любом месте справа от него.
 * Возврат заголовка измененного списка связей.
 *
 * Пример 1:
 * Вход: головка = [5,2,13,3,8]
 * Вывод: [13,8]
 * Пояснение: Необходимо удалить 5, 2 и 3 узлов.
 * - Узел 13 находится справа от узла 5.
 * - Узел 13 находится справа от узла 2.
 * - Узел 8 находится справа от узла 3.
 *
 * Пример 2:
 * Вход: head = [1,1,1,1]
 * Выходные данные: [1,1,1,1]
 * Объяснение: Каждый узел имеет значение 1, поэтому узлы не удаляются.
 *
 * Ограничения:
 * Число узлов в данном списке находится в диапазоне [1, 10^5].
 * 1 <= Node.val <= 10^5
 */
ListNode *removeNodes(ListNode *head)
{
    if (head == nullptr) {
        return nullptr;
    }
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast) {
        if (slow->val < fast->val) {
            if (head->val >= fast->val) {
                ListNode *current = head;
                while (current && current->next && current->next->val >= fast->val) {
                    current = current->next;
                }
                current->next = fast;
            } else {
                head = fast;
            }
        }
        slow = slow->next;
        fast = fast->next;
    }
    return head;
}

/*!
 * \brief doubleIt - Вы получаете заголовок непустого связанного списка, представляющего
 * неотрицательное целое число без начальных нулей. Верните заголовок связанного списка после
 * его
 * удвоения.
 *
 * Пример 1:
 * Вход: head = [1,8,9]
 * Выходные данные: [3,7,8]
 * Пояснение: Приведенный выше рисунок соответствует данному связному списку, который
 представляет
 * число 189. Следовательно, возвращенный связанный список представляет число 189 * 2 = 378.
 *
 * Пример 2:
 * Вход: head = [9,9,9]
 * Результат: [1,9,9,8]
 * Пояснение: Приведенный выше рисунок соответствует данному связному списку, который
 * представляет
 * число 999. Таким образом, возвращенный связанный список представляет собой номер 999 * 2 =
 * 1998.
 *
 * Ограничения:
 * Число узлов в списке находится в диапазоне [1, 10^4]
 * 0 <= Node.val <= 9
 * Входные данные генерируются таким образом, что список представляет число, которое не имеет
 * начальных нулей, за исключением самого числа 0.
 */
ListNode *doubleIt(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *current = head;

    // Инвертируем список
    while (current) {
        ListNode *temp = current;
        current = current->next;
        temp->next = prev;
        prev = temp;
    }

    // Умножение столбиком и обратная инвертация
    int remainder = 0;
    while (prev) {
        ListNode *temp = prev;
        prev = prev->next;
        temp->next = current;
        current = temp;
        int sum = (current->val * 2) + remainder;
        remainder = sum / 10;
        current->val = sum % 10;
    }
    return remainder ? new ListNode(remainder, current) : current;
}

/*!
 * \brief asteroidsDestroyed - Вам дается целочисленная масса, представляющая исходную массу
 * планеты. Далее даётся целый массив астероидов, где астероиды [i] - масса i-го астероида.
 * Можно организовать столкновение планеты с астероидами в любом произвольном порядке. Если
 * масса планеты больше или равна массе астероида, астероид разрушается и планета набирает массу
 * астероида. В противном случае планета разрушается. Возвращает значение true, если все
 * астероиды могут быть уничтожены. В противном случае возвращает значение false.
 *
 * Пример 1:
 * Ввод: mass = 10, asteroids = [3,9,19,5,21]
 * Вывод: true
 * Объяснение: Один из способов упорядочить астероиды - [9,19,5,3,21]:
 * - планета сталкивается с астероидом массой 9. Масса новой планеты: 10 + 9 = 19
 * - планета сталкивается с астероидом массой 19. Масса новой планеты: 19 + 19 = 38
 * - планета сталкивается с астероидом массой 5. Масса новой планеты: 38 + 5 = 43
 * - планета сталкивается с астероидом массой 3. Масса новой планеты: 43 + 3 = 46
 * - планета сталкивается с астероидом массой 21. Масса новой планеты: 46 + 21 = 67
 * Все астероиды уничтожены.
 *
 * Пример 2:
 * Вход: mass = 5, asteroids = [4,9,23,4]
 * Вывод: false
 *
 * Объяснение:
 * Планета никогда не может набрать достаточно массы, чтобы уничтожить астероид с массой 23.
 * После того, как планета уничтожит другие астероиды, она будет иметь массу 5 + 4 + 9 + 4 = 22.
 * Это меньше 23, поэтому столкновение не уничтожит последний астероид.
 *
 * Ограничения:
 * 1 <= масса < = 10^5
 * 1 <= asteroids.length <= 10^5
 * 1 <= астероиды[i] < = 10^5
 */
bool asteroidsDestroyed(int mass, vector<int> &asteroids)
{
    std::sort(asteroids.begin(), asteroids.end());
    for (int asteroid : asteroids) {
        if (mass < asteroid) {
            return false;
        }
        mass += asteroid;
    }
    return true;
}

/*!
 * \brief canBeEqual - Предоставляется два целочисленных массива одинаковой длины target и arr.
 * За один шаг можно выбрать любой непустой подчисток arr и обратить его. Можно выполнить любое
 * количество шагов. Возвращает значение true, если arr равен цели или false в противном случае.
 *
 * Пример 1:
 * Ввод: target = [1,2,3,4], arr = [2,4,1,3]
 * Вывод: true
 * Объяснение: Чтобы преобразовать arr в цель, выполните следующие действия:
 * 1 - Обратный подчисток [2,4,1], arr становится [1,4,2,3]
 * 2 - Обратный подчисток [4,2], arr становится [1,2,4,3]
 * 3 - Обратный подчисток [4,3], arr становится [1,2,3,4]
 * Существует несколько способов преобразования arr в target, это не единственный способ сделать
 * это.
 *
 * Пример 2: Вход: target = [7], arr = [7] Вывод: истина Объяснение: arr равен цели без
 * реверсов.
 *
 * Пример 3: Ввод: target = [3,7,9], arr = [3,7,11] Вывод: ложь Объяснение: arr не имеет
 * значения 9 и никогда не может быть преобразован в цель.
 *
 * Ограничения:
 * target.length == arr.length
 * 1 <= target.length <= 1000
 * 1 <= target[i] <= 1000
 * 1 <= arr[i] <= 1000
 */
bool canBeEqual(vector<int> &target, vector<int> &arr)
{
    using Type = vector<int>::size_type;
    const Type n = arr.size();
    std::unordered_map<int, int> counter;
    for (Type i = 0; i < n; ++i) {
        counter[target[i]] += 1;
        counter[arr[i]] -= 1;
    }

    for (auto it = counter.begin(); it != counter.end(); ++it) {
        if (it->second != 0) {
            return false;
        }
    }
    return true;
}

/*!
 * \brief appendCharacters - Вам даны две строки s и t, состоящие только из строчных английских
 * букв. Возвращает минимальное количество символов, которые необходимо добавить к концу s,
 * чтобы t стал подпоследовательностью s. Подпоследовательность - это строка, которая может быть
 * получена из другой строки путем удаления некоторых символов или их отсутствия без изменения
 * порядка остальных символов.
 *
 * Пример 1:
 * Вход: s = «coaching», t = «coding»
 * Выход: 4
 * Пояснение: Добавьте символы «ding» в конец s, чтобы s = «coachinging».
 * Теперь t является подпоследовательностью s («coachinging»).
 * Можно показать, что добавление любых 3 символов в конец s никогда не будет
 * подпоследовательностью.
 *
 * Пример 2: Вход: s = «abcde», t = «a» Вывод: 0 Объяснение: t уже является
 * подпоследовательностью s («abcde»). Пример 3: Вход: s = «z», t = «abcde» Выход: 5 Пояснение:
 * Добавьте символы «abcde» в конец s, чтобы s = «zabcde». Теперь t является
 * подпоследовательностью s («zabcde»). Можно показать, что добавление любых 4 символов в конец
 * s никогда не будет подпоследовательностью.
 *
 * Ограничения:
 * 1 <= s.length, t.length <= 10^5
 * s и t состоят только из строчных английских букв.
 */
int appendCharacters(string s, string t)
{
    using Type = string::size_type;
    Type index_s = 0;
    Type index_t = 0;
    while (index_s < s.size() && index_t < t.size()) {
        char c_s = s[index_s];
        char c_t = t[index_t];

        if (c_s == c_t) {
            ++index_t;
        }

        ++index_s;
    }
    return t.size() - index_t;
}

/*!
 * \brief longestPalindrome - Учитывая строку s, состоящую из строчных или прописных букв,
 * возвращает длину самого длинного палиндром которые можно построить с помощью этих букв. Буквы
 * чувствительны к регистру, например, «Aa» не считается палиндромом.
 *
 * Пример 1:
 * Вход: s = «abccccdd»
 * Выход: 7
 * Объяснение: Самый длинный палиндром, который можно построить, это «dccaccd», длина которого
 * составляет 7.
 *
 * Пример 2: Вход: s = «a» Вывод: 1 Объяснение: Самый длинный палиндром, который
 * можно построить - «а», длина которого равна 1.
 *
 * Ограничения:
 * 1 <= s.length <= 2000 \
 * s состоит только из строчных и/или прописных английских букв.
 */
int longestPalindrome(string s)
{
    std::unordered_map<char, int> dict;

    // Количество строчных и прописных букв английского алфавита составляет 52, но чтобы
    // снизить количество колизий в хэш таблице к нулю резервируем в два раза больше
    dict.reserve(104);

    for (char c : s) {
        dict[c] += 1;
    }

    int ans = 0;
    bool flag = false;
    for (const auto &p : dict) {
        if (p.second % 2 == 0) {
            ans += p.second;
        } else {
            flag = true;
            ans += p.second - 1;
        }
    }
    if (flag) {
        ++ans;
    }
    return ans;
}

/*!
 * \brief commonChars - При наличии строкового массива слов возвращает массив из всех символов,
 * отображаемых во всех строках в словах (включая дубликаты). Вы можете вернуть ответ в любом
 * порядке.
 *
 * Пример 1:
 * Ввод: слова = [«bella», label, roller]
 * Выходные данные: [«e», «l», «l»]
 *
 * Пример 2:
 * Ввод: слова = [«cool», «lock», «cook»]
 * Вывод: [«c», «o»]
 *
 * Ограничения:
 * 1 <= words.length <= 100
 * 1 <= words[i].length <= 100
 * word[i] состоит из строчных английских букв.
 */
vector<string> commonChars(vector<string> &words)
{
    vector<string> ans;
    for (char c : words.front()) {
        bool flag = true;
        for (size_t i = 1; i < words.size(); ++i) {
            string &word = words[i];
            string::size_type pos = word.find(c);
            if (pos != string::npos) {
                word.replace(pos, 1, "*");
            } else {
                flag = false;
                break;
            }
        }
        if (flag) {
            ans.emplace_back(std::string(1, c));
        }
    }
    return ans;
}

/*!
 * \brief isNStraightHand - У Алисы есть некоторое количество карт, и она хочет перегруппировать
 * карты в группы, чтобы каждая группа имела размер groupSize, и состоит из groupSize
 * последовательных карт. При целочисленном массиве, где hand [i] - значение, записанное на i-ой
 * карточке, и целое groupSize, возвращайте true, если она может переупорядочить карточки, или
 * false в противном случае.
 *
 * Пример 1:
 * Ввод: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
 * Вывод: true
 * Объяснение: руку Алисы можно переставить как [1,2,3], [2,3,4], [6,7,8]
 *
 * Пример 2:
 * Ввод: hand = [1,2,3,4,5], groupSize = 4
 * Вывод: false
 * Объяснение: руку Алисы нельзя перегруппировать в группы по 4.
 *
 *
 * Ограничения:
 * 1 <= hand.length <= 10^4
 * 0 < = hand[i] < = 10^9
 * 1 <= groupSize <= hand.length
 */
bool isNStraightHand(vector<int> &hand, int groupSize)
{
    std::map<int, int> cardCount;
    for (int card : hand) {
        ++cardCount[card];
    }
    for (const auto &p : cardCount) {
        if (p.second <= 0) {
            continue;
        }
        for (int i = p.first; i < p.first + groupSize;) {
            if ((--cardCount[i++]) < 0) {
                return false;
            }
        }
    }
    return true;
}

/*!
 * \brief replaceWords - В английском языке у нас есть понятие под названием root, за которым
 * может следовать какое-то другое слово для образования другого более длинного слова - назовем
 * это слово производным. Например, когда за корнем «help» следует слово «ful», мы можем
 * образовать производное «helpful». Учитывая словарь, состоящий из множества корней и
 * предложения, состоящего из слов, разделённых пробелами, заменить все производные в
 * предложении на образующий его корень. Если производная может быть заменена несколькими
 * корнями, замените ее корнем, имеющим самую короткую длину. Верните предложение после замены.
 *
 * Пример 1:
 * Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
 * Output: "the cat was rat by the bat"
 *
 * Пример 2:
 * Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
 * Output: "a a b c"
 *
 * Ограничения:
 * 1 <= dictionary.length <= 1000
 * 1 <= dictionary[i].length <= 100
 * dictionary[i] состоит только из строчных букв.
 * 1 <= sentence.length <= 10^6 предложение состоит только из строчных букв и пробелов.
 * Число слов в предложении находится в диапазоне [1, 1000]
 * Длина каждого слова в предложении находится в диапазоне [1, 1000]
 * Каждые два последовательных слова в предложении будут разделены ровно одним пробелом.
 * предложение не имеет начальных или конечных пробелов.
 */
string replaceWords(vector<string> &dictionary, string sentence)
{
    std::unordered_set<std::string> hashDict(dictionary.begin(), dictionary.end());
    sentence.push_back(' ');

    std::string ans;
    std::string temp;
    for (int i = 0; i < (int) sentence.size(); ++i) {
        if (std::isspace(sentence[i])) {
            ans += temp;
            ans += ' ';
            temp.clear();
        } else {
            temp += sentence[i];
            if (hashDict.count(temp)) {
                ans += temp;
                ans += ' ';
                temp.clear();
                ++i;
                while (!std::isspace(sentence[i])) {
                    ++i;
                }
            }
        }
    }
    ans.pop_back();
    return ans;
}

/*!
 * \brief heightChecker - Школа пытается сделать ежегодное фото всех учеников. Студентов просят
 * стоять в одной строке файла в неубывающем порядке по высоте. Пусть это упорядочение будет
 * представлено целочисленным массивом, ожидаемым где [i] - ожидаемая высота i-го студента в
 * строке. Задается целочисленная высота массива, представляющая текущий порядок, в котором
 * находятся ученики. Каждая высота [i] - высота i-го ученика в строке (0-индексированная).
 * Возвращает число индексов, в которых высота [i]! = ожидаемая [i].
 *
 * Example 1:
 * Input: heights = [1,1,4,2,1,3]
 * Output: 3
 * Explanation:
 * heights:  [1,1,4,2,1,3]
 * expected: [1,1,1,2,3,4]
 * Indices 2, 4, and 5 do not match.
 *
 * Example 2:
 * Input: heights = [5,1,2,3,4]
 * Output: 5
 * Explanation:
 * heights:  [5,1,2,3,4]
 * expected: [1,2,3,4,5]
 * All indices do not match.
 *
 * Example 3:
 * Input: heights = [1,2,3,4,5]
 * Output: 0
 * Explanation:
 * heights:  [1,2,3,4,5]
 * expected: [1,2,3,4,5]
 * All indices match.
 *
 * Ограничения:
 * 1 <= heights.length <= 100
 * 1 <= height[i] <= 100
 */
int heightChecker(vector<int> &heights)
{
    int ans = 0;
    const std::vector<int>::size_type n = heights.size();
    std::vector<int> temp(heights);
    std::sort(temp.begin(), temp.end());
    for (std::vector<int>::size_type i = 0; i < n; ++i) {
        if (heights[i] != temp[i]) {
            ++ans;
        }
    }
    return ans;
}

/*!
 * \brief getMinDistance - Учитывая целочисленные числа массива (0-индексированные) и два
 * целочисленных target и start числа, найдите индекс i, так что nums[i] = target и
 * abs (i - start) минимизируются. Обратите внимание, что abs (x) является абсолютным значением
 * x. Возврат abs (i - начало). Гарантируется, что цель существует в числах.
 *
 * Example 1:
 * Input: nums = [1,2,3,4,5], target = 5, start = 3
 * Output: 1
 * Explanation: nums[4] = 5 is the only value equal to target, so the answer is abs(4 - 3) = 1.
 *
 * Example 2:
 * Input: nums = [1], target = 1, start = 0
 * Output: 0
 * Explanation: nums[0] = 1 is the only value equal to target, so the answer is abs(0 - 0) = 0.
 *
 * Example 3:
 * Input: nums = [1,1,1,1,1,1,1,1,1,1], target = 1, start = 0
 * Output: 0
 * Explanation: Every value of nums is 1,
 * but nums[0] minimizes abs(i - start), which is abs(0 - 0) = 0.
 *
 * Constraints:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 10^4
 * 0 <= start < nums.length
 * target is in nums.
 */
int getMinDistance(vector<int> &nums, int target, int start)
{
    if (nums[start] == target) {
        return 0;
    }

    int i = start + 1, j = start - 1;
    while (true) {
        if (i >= 0 && nums[i] == target) {
            return i - start;
        }
        if (j < (int) nums.size() && nums[j] == target) {
            return start - j;
        }
        ++i;
        --j;
    }
    return -1;
}

/*!
 * \brief minMovesToSeat - В комнате есть n мест и n студентов. Вам дается массив посадочных
 * мест длиной n, где посадочные места [i] - положение i-го посадочного места. Вам также дается
 * массив студентов длиной n, где студенты [j] является положением j-го студента. Вы можете
 * выполнить следующее перемещение любое количество раз: Увеличение или уменьшение положения
 * i-го учащегося на 1 (т.е. перемещение i-го учащегося из положения x в положение x + 1 или x -
 * 1) Возвращает минимальное количество перемещений, необходимое для перемещения каждого ученика
 * на место, чтобы ни один ученик не находился в одном месте. Обратите внимание, что в начале
 * может быть несколько мест или студентов в одной позиции.
 *
 * Пример 1:
 * Входные данные: места = [3,1,5], студенты = [2,7,4]
 * Выход: 4
 * Объяснение: Студенты перемещаются следующим образом:
 * - Первый ученик перемещается из положения 2 в положение 1, используя 1 ход.
 * Второй ученик перемещается из положения 7 в положение 5 с помощью 2 ходов.
 * - Третий ученик перемещается из положения 4 в положение 3, используя 1 ход.
 * Всего было использовано 1 + 2 + 1 = 4 хода.
 *
 * Пример 2:
 * Входные данные: места = [4,1,5,9], студенты = [1,3,2,6]
 * Выход: 7
 * Объяснение: Студенты перемещаются следующим образом:
 * - Первый ученик не перемещен.
 * Второй ученик перемещается из положения 3 в положение 4, используя 1 ход.
 * Третий ученик перемещается из положения 2 в положение 5 с помощью 3 ходов.
 * - Четвертый ученик перемещается из положения 6 в положение 9 с помощью 3 ходов.
 * Всего было использовано 0 + 1 + 3 + 3 = 7 ходов.
 *
 * Пример 3:
 * Входные данные: места = [2,2,6,6], студенты = [1,3,2,6]
 * Выход: 4
 * Пояснение: Обратите внимание, что имеется два места в положении 2 и два места в положении 6.
 * Учащиеся перемещаются следующим образом:
 * - Первый ученик перемещается из положения 1 в положение 2, используя 1 ход.
 * Второй ученик перемещается из положения 3 в положение 6 с помощью 3 ходов.
 * - Третий ученик не перемещен.
 * - Четвертый ученик не перемещен.
 * Всего было использовано 1 + 3 + 0 + 0 = 4 хода.
 *
 * Ограничения:
 * n == seats.length == students.length
 * 1 <= n <= 100
 * 1 <= seats[i], students [j] <= 100
 */
int minMovesToSeat(vector<int> &seats, vector<int> &students)
{
    int ans = 0;

    boost::sort::spreadsort::integer_sort(seats.begin(), seats.end());
    boost::sort::spreadsort::integer_sort(students.begin(), students.end());

    auto it = seats.begin(), jt = students.begin();
    while (it != seats.end() && jt != students.end()) {
        ans += std::abs((*(it++)) - (*(jt++)));
    }
    return ans;
}

/*!
 * \brief removeOccurrences - Учитывая две строки s и part, выполните следующую операцию над s
 * до тех пор, пока все вхождения детали подстроки не будут удалены: Найдите крайнее левое
 * вхождение part подстроки и удалите ее из s. Возвращает s после удаления всех вхождений
 детали.
 * Подстрока - это непрерывная последовательность символов в строке.
 *
 * Пример 1:
 * Вход: s = «daabcbaabcbc», part = «abc»
 * Вывод: «dab»
 * Пояснение: Выполняются следующие операции:
 * - s = «daabcbaabcbc», удалить «abc» начиная с индекса 2, поэтому s = «dabaabcbc».
 * - s = «dabaabcbc», удалить «abc» начиная с индекса 4, поэтому s = «dababc».
 * - s = «dababc», удалить «abc» начиная с индекса 3, поэтому s = «dab».
 * Теперь s не имеет вхождений «abc».

 * Пример 2:
 * Вход: s = «axxxxyyyyb», часть = «xy»
 * Вывод: «ab»
 * Пояснение: Выполняются следующие операции:
 * - s = «axxxxyyyyb», удалите «xy», начинающийся в индексе 4 так s = «axxxyyyb».
 * - s = «axxxyyyb», удалить «xy» начиная с индекса 3, так что s = «axxyyb».
 * - s = «axxyyb», удалить «xy» начиная с индекса 2, так что s = «axyb».
 * - s = «axyb», удалить «xy» начиная с индекса 1, так что s = «ab».
 * Теперь s не имеет вхождений «xy».

 * Ограничения:
 * 1 <= s.length <= 1000
 * 1 <= part.length <= 1000
 * s и часть состоит из строчных английских букв.
 */
string removeOccurrences(string s, string part)
{
    string::size_type index = string::npos;
    while ((index = s.find(part)) != string::npos) {
        s.erase(index, part.size());
    }
    return s;
}

/*!
 * \brief minIncrementForUnique - Предоставляется целое число массива. За один ход можно выбрать
 * индекс i, где 0 <= i < nums.length и приращение чисел [i] на 1. Возвращает минимальное число
 * перемещений, чтобы сделать каждое значение в числах уникальным. Тестовые примеры генерируются
 * таким образом, что ответ помещается в 32-битное целое число.
 *
 * Пример 1:
 * Ввод: числа = [1,2,2]
 * Вывод: 1
 * Объяснение: После 1 хода массив может быть [1, 2, 3].
 *
 * Пример 2:
 * Ввод: числа = [3,2,1,2,1,7]
 * Выходные данные: 6
 * Объяснение: После 6 ходов массив может быть [3, 4, 1, 2, 5, 7].
 * Можно показать 5 или менее ходов, что массив не может иметь все уникальные значения.
 *
 * Ограничения:
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^5
 */
int minIncrementForUnique(vector<int> &nums)
{
    boost::sort::spreadsort::integer_sort(nums.begin(), nums.end());
    int ans = 0;
    for (vector<int>::size_type i = 1; i < nums.size(); ++i) {
        if (nums[i] <= nums[i - 1]) {
            int target = nums[i - 1] + 1;
            ans += target - nums[i];
            nums[i] = target;
        }
    }
    return ans;
}

/*!
 * \brief maxProfitAssignment - У вас есть n рабочих и m работников. Вы получили три массива:
 * difficulty, profit и worker, где: difficulty[i] и profit[i] - это трудность и прибыль
 * i-ой работы, а worker[j] - это способность j-го работника (т.е. j-й работник может
 * выполнить работу только с трудом в большинстве случаев [j]). Каждому работнику может быть
 * назначено не более одного задания, но одно задание может быть выполнено несколько раз.
 * Например, если три работника попытаются выполнить одну и ту же работу, которая оплачивает $1,
 * то общая прибыль составит $3. Если работник не может выполнить какое-либо задание, его
 * прибыль составляет 0 долларов. Верните максимальную прибыль, которую мы можем получить после
 * назначения работников на работу.
 *
 * Пример 1:
 * Входные данные: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
 * Выход: 100
 * Объяснение: Работники получают трудную работу [4,4,6,6] и получают прибыль в размере
 * [20,20,30,30] отдельно.
 *
 * Пример 2:
 * Ввод: difficulty = [85,47,57], profit = [24,66,99], worker = [40,25,25]
 * Вывод: 0
 *
 * Ограничения:
 * n == difficulty.length
 * n == profit.length
 * m == worker.length
 * 1 <= n, m <= 10^4
 * 1 <= difficulty[i], profit[i], worker[i] <= 10^5
 */
int maxProfitAssignment(vector<int> &difficulty, vector<int> &profit, vector<int> &worker)
{

    /* Сортировка данных*/
    // 1) Приоритетная очередь сортируется по паре "Трудность-прибыль", где
    // самая большая прибыль будет самым верхним элементом приоритетной очереди
    // 2) Сортировка работников, для того чтобы знать, что если верхний работник не может
    // справиться с задачей с самой большой прибылью, то и остальные не смогут
    auto comp = [](const std::pair<int, int> &first,
                   const std::pair<int, int> &second) -> bool {
        return first.second < second.second;
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)>
        pq(comp);
    for (int i = 0; i < (int) difficulty.size(); ++i) {
        pq.push(std::make_pair(difficulty[i], profit[i]));
    }
    std::sort(worker.begin(), worker.end());
    /* Конец сортировки */

    // Далее просто производим расчёт по отсортированным данным
    int ans = 0;
    int i = worker.size() - 1;
    while (!pq.empty() && i >= 0) {
        if (worker[i] < pq.top().first) {
            // Здесь работник не состояние выполнить работу.
            // И так как у этого работника самая большая работаспособность из-за
            // отсортированности массива, то единственное что мы можем сделать это выкинуть
            // текущую работу из очереди, так как ёё никто не сможет выполнить из работников.
            pq.pop();
        } else {
            // Здесь работник в состояние выполнить работу.
            // Значит все что нам надо сделать это прибавить к ответу прибыль и уменьшить
            // итерацию i работника
            ans += pq.top().second;
            --i;
        }
    }
    return ans;
    /* Time - N*log(N), Memory - O(N) */
}

/*!
 * \brief minDays - Предоставляется целочисленный массив bloomDay, целое число m и целое число
 * k. Мы хотим сделать m букетов. Чтобы сделать букет, нужно использовать k смежных цветов из
 * сада. Сад состоит из n цветов, i-й цветок будет цвести в bloomDay [i] и затем может быть
 * использован ровно в одном букете. Верните минимальное количество дней, которое нужно
 * подождать, чтобы иметь возможность сделать м букетов из сада. Если невозможно сделать м
 * букетов вернуть -1.
 *
 * Пример 1:
 * Вход: bloomDay = [1,10,3,10,2], m = 3, k = 1
 * Выходные данные: 3
 * Объяснение: Посмотрим, что произошло в первые три дня. х означает цветок зацвёл и _ значит
 * цветок не зацвёл в саду. Нам нужно 3 букета каждый должен содержать 1 цветок.
 * После 1 дня: [x, _, _, _, _ ]//мы можем сделать только один букет.
 * После 2 дня: [x, _, _, _, x ]//мы можем сделать только два букета.
 * После 3 дня: [x, _, x, _, x ]//мы можем сделать 3 букета.
 * Ответ - 3.
 *
 * Пример 2:
 * Вход: bloomDay = [1,10,3,10,2], m = 3, k = 2
 * Вывод: -1
 * Объяснение: Нам нужно 3 букета каждый имеет 2 цветка, то есть нам нужно 6 цветов. У нас всего
 * 5 цветов, поэтому невозможно получить нужные букеты и мы возвращаемся -1.
 *
 * Пример 3: Входные
 * данные: bloomDay = [7,7,7,7,12,7,7], m = 2, k = 3
 * Выход: 12
 * Объяснение: Нам нужно 2 букета каждый должен иметь 3 цветка.
 * Вот сад после 7 и 12 дней:
 * После дня 7: [x, x, x, x, _, x, x] Мы можем сделать один букет из первых трех цветков,
 * которые зацвели. Мы не можем сделать еще один букет из трех последних цветов, которые
 * зацвели, потому что они не соседствуют.
 * После 12 дня: [x, x, x, x, x, x, x, x] Очевидно, что два букета мы можем сделать по-разному.
 *
 * Ограничения:
 * bloomDay.length == n
 * 1 <= n <= 10^5
 * 1 <= bloomDay [i] <= 10^9
 * 1 <= m <= 10^6
 * 1 <= k <= n
 */
int getBouquetCount(const vector<int> &bloomDay, int k, int waitingDays)
{
    //Возвращает количество букетов (требуется k цветов), которые можно сделать после
    //'дни ожидания'.
    int bouquetCount = 0;
    int requiredFlowers = k;

    for (const int day : bloomDay) {
        if (day > waitingDays) {
            // Сбросить «требуемые цветы», так как не хватает смежных цветов.
            requiredFlowers = k;
        } else if ((--requiredFlowers) == 0) {
            // Используйте k соседних цветов, чтобы сделать букет.
            ++bouquetCount;
            requiredFlowers = k;
        }
    }
    return bouquetCount;
}

int minDays(vector<int> &bloomDay, int m, int k)
{
    if (bloomDay.size() < static_cast<vector<int>::size_type>(m) * k) {
        return -1;
    }

    auto min_max = std::minmax_element(bloomDay.begin(), bloomDay.end());
    int left = *min_max.first;
    int right = *min_max.second;
    while (left < right) {
        const int mid = (left + right) / 2;
        if (getBouquetCount(bloomDay, k, mid) >= m) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

/*!
 * \brief maxSatisfied - Есть владелец книжного магазина, у которого магазин открыт на n минут.
 * Каждую минуту в магазин заходит некоторое количество покупателей. Вам дается целочисленный
 * массив клиентов длиной n, где customers[i] - это число клиентов, которые входят в магазин в
 * начале i-й минуты, и все эти клиенты уходят после окончания этой минуты.
 * В несколько минут владелец книжного магазина ворчит. Если владелец книжного магазина ворчит в
 * течение i-й минуты и равен 0, то вам предоставляется бинарный массив grumpy, где grumpy [i]
 * равно 1. Когда владелец книжного магазина сварлив, клиенты той минуты не довольны, в
 * противном случае
 * - довольны. Владелец книжного магазина знает секретную технику, чтобы держать себя не grumpy
 * в течение нескольких минут подряд, но может использовать ее только один раз. Верните
 * максимальное количество клиентов, которые могут быть удовлетворены в течение дня.
 *
 * Пример 1:
 * Ввод: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
 * Выход: 16
 * Объяснение: Владелец книжного магазина держит себя не сварливыми последние 3 минут.
 * Максимальное количество клиентов, которые могут
 * быть удовлетворены = 1 + 1 + 1 + 1 + 7 + 5 = 16.
 *
 * Пример 2:
 * Ввод: customers = [1], grumpy = [0], minutes = 1
 * Вывод: 1
 *
 * Ограничения:
 * n == customers.length == grumpy.length
 * 1 <= minutes <= n <= 2 * 10^4
 * 0 <= customers[i] <= 1000
 * grumpy[i] равно 0 или 1.
 */
int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int minutes)
{
    // ** Условия **
    // 1) Магазин открыт на n минут, то есть на размер массива customers и grumpy
    // 2) customers[i] - это число клиентов, которые входят в магазин в начале i-й минуты, и все
    // эти клиенты уходят после окончания этой минуты
    // 3) Когда grumpy[i] = 1, то customers[i] не удовлетворены и не будут учитываться в ответе
    // 4) У владельца есть единоразовая способность чтобы не ворчать "minutes - целое число" и
    // клиенты будут довольны

    const int n = (int) customers.size();
    int maxDissCustomers = 0, index = 0, summ = 0;

    while (index < minutes) {
        if (grumpy[index] == 1) {
            maxDissCustomers += customers[index];
        } else {
            summ += customers[index];
        }
        ++index;
    }

    int curDissCustomers = maxDissCustomers;

    while (index < n) {
        if (grumpy[index - minutes] == 1) {
            curDissCustomers -= customers[index - minutes];
        }

        if (grumpy[index] == 1) {
            curDissCustomers += customers[index];
        } else {
            summ += customers[index];
        }

        maxDissCustomers = std::max(curDissCustomers, maxDissCustomers);
        ++index;
    }

    return summ + maxDissCustomers;
}

/*!
 * \brief minDifference - Предоставляется целое число массива.
 * За один ход можно выбрать один элемент чисел и изменить его на любое значение.
 * Возвращает минимальную разницу между наибольшим и наименьшим значениями чисел после
 * выполнения не более трех ходов.
 *
 * Пример 1:
 * Ввод: числа = [5,3,2,4]
 * Вывод: 0
 * Объяснение: Мы можем сделать не более 3 ходов.
 * При первом перемещении измените значение 2 на 3. числа становятся [5,3,3,4].
 * Во втором движении измените значение 4 на 3. числа становятся [5,3,3,3].
 * На третьем ходу измените 5 на 3. числа становятся [3,3,3,3].
 * После выполнения 3 ходов разница между минимальным и максимальным составляет 3 - 3 = 0.
 *
 * Пример 2:
 * Ввод: числа = [1,5,0,10,14]
 * Вывод: 1
 * Объяснение: Мы можем сделать не более 3 ходов.
 * При первом перемещении измените значение 5 на 0. nums становится [1,0,0,10,14].
 * Во втором перемещении измените значение 10 на 0. nums становится [1,0,0,0,14].
 * На третьем ходу измените 14 на 1. числа становятся [1,0,0,0,1].
 * После выполнения 3 ходов разница между минимальным и максимальным составляет 1 - 0 = 1.
 * Можно показать, что нет возможности сделать разницу 0 в 3 ходах.
 *
 * Пример 3:
 * Ввод: числа = [3,100,20]
 * Вывод: 0
 * Объяснение: Мы можем сделать не более 3 ходов.
 * При первом перемещении измените значение 100 на 7. числа становятся [3,7,20].
 * Во втором движении измените 20 на 7. числа становятся [3,7,7].
 * На третьем ходу измените 3 на 7. числа становятся [7,7,7].
 * После выполнения 3 ходов разница между минимальным и максимальным составляет 7 - 7 = 0.
 *
 * Ограничения:
 * 1 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 */
int minDifference(vector<int> &nums)
{
    const int n = nums.size();
    if (n < 5) {
        return 0;
    }
    int ans = INT_MAX;
    boost::sort::spreadsort::integer_sort(nums.begin(), nums.end());
    for (int i = 0; i <= 3; ++i) {
        ans = std::min(ans, nums[n - 4 + i] - nums[i]);
    }
    return ans;
}

/*!
 * \brief mergeNodes - Вы получаете заголовок связанного списка, который содержит ряд целых
 * чисел, разделенных 0. Начало и конец связанного списка будут иметь Node.val == 0. Для каждых
 * двух последовательных нулей объединяйте все узлы, лежащие между ними, в один узел, значение
 * которого является суммой всех объединенных узлов. Измененный список не должен содержать
 * нулей. Возврат заголовка измененного списка связей.
 *
 * Пример 1:
 * Ввод: head = [0,3,1,0,4,5,2,0]
 * Выходные данные: [4,11]
 * Объяснение:
 * На приведенном выше рисунке представлен данный связанный список. Измененный список содержит
 * - Сумма узлов, помеченных зеленым цветом: 3 + 1 = 4.
 * - Сумма узлов, отмеченных красным цветом: 4 + 5 + 2 = 11.
 * Пример 2:
 * Ввод: head = [0,1,0,3,0,2,2,0]
 * Выход: [1,3,4]
 * Объяснение:
 * На приведенном выше рисунке представлен данный связанный список. Измененный список содержит
 * - Сумма узлов, помеченных зеленым цветом: 1 = 1.
 * - Сумма узлов, помеченных красным цветом: 3 = 3.
 * - Сумма узлов, отмеченных желтым цветом: 2 + 2 = 4.
 *
 * Ограничения:
 * Число узлов в списке находится в диапазоне [3, 2 * 105].
 * 0 <= Node.val <= 1000
 * Нет двух последовательных узлов с Node.val == 0.
 * Начало и конец связанного списка имеют Node.val == 0.
 */
ListNode *mergeNodes(ListNode *head)
{
    if (!head) {
        return nullptr;
    }

    while (head && head->val == 0) {
        head = head->next;
    }

    ListNode *newHead = nullptr;
    ListNode *temp = nullptr;
    int sum = 0;

    while (head) {
        if (head->val == 0) {
            if (newHead) {
                temp->next = new ListNode(sum);
                temp = temp->next;
            } else {
                newHead = new ListNode(sum);
                temp = newHead;
            }
            sum = 0;
        } else {
            sum += head->val;
        }
        head = head->next;
    }
    return newHead;
}

/*!
 * \brief averageWaitingTime - Есть ресторан с единственным шеф-поваром. Вам предоставляется
 * массив заказчиков, где клиенты [i] = [arrivali, timei]: arrivali - время прибытия i-го
 * клиента.
 * Время поступления сортируется в неубывающем порядке. timei - время, необходимое для
 * подготовки
 * заказа i-го клиента. Когда клиент приходит, он отдает шеф-повару свой заказ, и шеф-повар
 * начинает его готовить, как только он простаивает. Клиент ждет, пока шеф-повар закончит
 * подготовку своего заказа. Шеф-повар не готовит еду для более чем одного клиента одновременно.
 * Шеф-повар готовит еду для клиентов в том порядке, в каком они были приведены. Возвращает
 * среднее
 * время ожидания всех клиентов. Решения в пределах 10^-5 от фактического ответа считаются
 * принятыми.
 *
 * Пример 1:
 * Ввод: клиенты = [[1,2], [2,5], [4,3]]
 * Выход: 5.00000
 * Объяснение:
 * 1) Первый клиент приходит в момент времени 1, шеф-повар берет свой заказ и начинает готовить
 * его
 * немедленно в момент времени 1, а заканчивает в момент времени 3, так что время ожидания
 * первого
 * клиента составляет 3 - 1 = 2.
 * 2) Второй клиент приходит в момент времени 2, шеф-повар берет свой
 * заказ и начинает его подготовку в момент времени 3, а заканчивает в момент времени 8, так что
 * время ожидания второго клиента составляет 8 - 2 = 6.
 * 3) Третий клиент приходит в момент времени 4, шеф-повар берет свой заказ и начинает его
 * подготовку в момент времени 8, а заканчивает в
 * момент времени 11, так что время ожидания третьего клиента 11 - 4 = 7. Среднее время ожидания
 * = (2 + 6 + 7 )/3 = 5.

 * Пример 2: Ввод: клиенты = [[5,2], [5,4], [10,3], [20,1]] Выход: 3.25000
 * Объяснение:
 * 1) Первый клиент приходит в момент времени 5, шеф-повар берет свой заказ и начинает готовить
 * его немедленно в момент времени 5, а заканчивает в момент времени 7, так что время ожидания
 * первого клиента 7 - 5 = 2.
 * 2) Второй клиент приходит в момент времени 5, шеф-повар берет свой
 * заказ и начинает его подготовку в момент времени 7, а заканчивает в момент времени 11, так
 * что
 * время ожидания второго клиента составляет 11 - 5 = 6. 3) Третий клиент приходит в момент
 * времени
 * 10, шеф-повар берет свой заказ и начинает его подготовку в момент времени 11, а заканчивает в
 * момент времени 14, так что время ожидания третьего клиента составляет 14 - 10 = 4. 4)
 * Четвертый
 * клиент приходит в момент времени 20, шеф-повар берет свой заказ и начинает готовить его сразу
 * в
 * момент времени 20, а заканчивает в момент времени 21, так что время ожидания четвертого
 * клиента
 * 21 - 20 = 1. Среднее время ожидания = (2 + 6 + 4 + 1 )/4 = 3,25.
 *
 * Ограничения:
 * 1 <= customers.length <= 10^5
 * 1 < = arrival[i], time[i] < = 10^4
 * прибытие[i] <= прибытие[i+1]
 */
double averageWaitingTime(vector<vector<int>> &customers)
{
    double summ = 0.0;    // Общее время ожидания клиентов
    int endTimePoint = 0; // Последний момент времени
    for (const vector<int> &customer : customers) {
        endTimePoint = std::max(endTimePoint, customer[0]) + customer[1];
        summ += endTimePoint - customer[0];
    }
    return summ / customers.size();
}

/*!
 * \brief reverseParentheses - Имеется строка s, состоящая из английских букв и скобок нижнего
 * регистра. переверните строки в каждой паре совпадающих скобок, начиная с самой внутренней.
 * Результат не должен содержать скобок.
 *
 * Пример 1:
 * Вход: s = «(abcd)»
 * Выход: «dcba»

 * Пример 2:
 * Вход: s = «(u(love)i)»
 * Выход: «iloveu»
 * Объяснение: Подстрока «love» сначала меняется на обратную, затем вся строка меняется на
 * обратную. Пример 3: Вход: s = «(ed (et (oc)) el)» Вывод: «leetcode» Объяснение: Сначала мы
 * обращаем подстроку «oc», затем «etco» и, наконец, всю строку.
 *
 * Ограничения:
 * 1 <= s.length <= 2000
 * s содержит только строчные английские символы и круглые скобки.
 * Гарантируется, что все круглые скобки сбалансированы.
 */
string reverseParentheses(string s)
{
    std::string ans;
    stack<int> st;
    for (const char c : s) {
        if (c == '(') {
            st.push(ans.length());
        } else if (c == ')') {
            int temp = st.top();
            st.pop();
            std::reverse(ans.begin() + temp, ans.end());
        } else {
            ans += c;
        }
    }
    return ans;
}

/*!
 * \brief maxProduct - Если задано целое число массива, найдите
 * подмножество который имеет самый большой продукт, и вернуть продукт.
 * Тестовые примеры генерируются таким образом, что ответ помещается в 32-битное целое число.
 *
 * Пример 1:
 * Вход: числа = [2,3, -2,4]
 * Выходные данные: 6
 * Объяснение: [2,3] имеет самый большой продукт 6.
 *
 * Пример 2:
 * Вход: числа = [-2,0, -1]
 * Вывод: 0
 * Объяснение: Результат не может быть 2, так как [-2, -1] не является подмассивом.
 *
 * Ограничения:
 * 1 <= nums.length <= 2 * 10^4
 * -10 <= числа [i] <= 10
 * Произведение любого префикса или суффикса чисел гарантированно помещается в 32-битное целое
 * число.
 */
int maxProduct(vector<int> &nums)
{
    const int n = nums.size();
    double ans = INT_MIN, left_to_right = 1, right_to_left = 1;
    for (int i = 0; i < n; ++i) {
        if (left_to_right == 0) {
            left_to_right = 1;
        }
        if (right_to_left == 0) {
            right_to_left = 1;
        }
        left_to_right *= nums[i];
        right_to_left *= nums[n - 1 - i];
        ans = std::max(std::max(left_to_right, right_to_left), ans);
    }
    return ans;
}

/*!
 * \brief findSubsequences - Учитывая целое число массива, возвращайте все различные возможные
 * неубывающие подпоследовательности данного массива, по крайней мере, с двумя элементами. Вы
 * можете вернуть ответ в любом порядке.
 *
 * Пример 1:
 * Ввод: числа = [4,6,7,7]
 * Выходные данные: [[4,6], [4,6,7], [4,6,7,7], [4,7], [4,7,7], [6,7], [6,7,7], [7,7]]
 *
 * Пример 2:
 * Ввод: числа = [4,4,3,2,1]
 * Вывод: [[4,4]]
 *
 * Ограничения:
 * 1 <= nums.length <= 15
 * -100 <= числа[i] <= 100
 */
void helperFindSubsequences(const vector<int> &nums, int s, vector<int> &&path,
                            vector<vector<int>> &ans)
{
    if (path.size() > 1) {
        ans.push_back(path);
    }

    unordered_set<int> used;

    for (int i = s; i < (int) nums.size(); ++i) {
        if (used.count(nums[i])) {
            continue;
        }

        if (path.empty() || path.back() <= nums[i]) {
            used.insert(nums[i]);
            path.push_back(nums[i]);
            helperFindSubsequences(nums, i + 1, std::move(path), ans);
            path.pop_back();
        }
    }
}

vector<vector<int>> findSubsequences(vector<int> &nums)
{
    vector<vector<int>> ans;
    helperFindSubsequences(nums, 0, {}, ans);
    return ans;
}

/*!
 * \brief getPairAscendingOrDescending - Вернуть индексы левой и правой границы самого большого
 * строго возрастающего или убывающего подмассива. Массив пустым быть не может.
 *
 * Пример - [7, 2, 1, -1, 3, 4, 7, 8], return {3, 7}
 */
pair<int, int> getPairAscendingOrDescending(const vector<int> &nums)
{
    pair<int, int> ans = {0, 0};
    const int n = (int) nums.size();
    int left = 0, right = 0, i = 1;
    while (i < n) {
        if (nums[i - 1] < nums[i]) {
            left = i - 1;
            while (i < n && nums[i - 1] < nums[i]) {
                ++i;
            }
            right = i - 1;
        } else if (nums[i - 1] > nums[i]) {
            left = i - 1;
            while (i < n && nums[i - 1] > nums[i]) {
                ++i;
            }
            right = i - 1;
        } else {
            ++i;
            continue;
        }

        // обновление значения
        if (ans.second - ans.first < right - left) {
            ans.first = left;
            ans.second = right;
        }
    }
    return ans;
}

/*!
 * \brief getPairTargetSumSubArray - Вернуть индексы левой и правой границы подмассива, такого
 * что сумма его чисел равна target, в противном случае вернуть {-1, -1}. Если таких подмассивов
 * несколько вернуть любую пару соответствующую задаче.
 *
 * Пример. nums=[-1, 3, 2, -7, 3, 4, -2, 10], target=7, return {4, 5} -> nums[4] + nums[5] == 7
 */
pair<int, int> getPairTargetSumSubArray(const vector<int> &nums, int target)
{
    const int n = (int) nums.size();
    std::unordered_map<long long, int> prefix_index = {{0, -1}};
    long long prefix = 0;
    for (int i = 0; i < n; ++i) {
        prefix += nums[i];
        auto it = prefix_index.find(prefix - target);
        if (it != prefix_index.end()) {
            return {it->second + 1, i};
        }
        prefix_index[prefix] = i;
    }
    return {-1, -1};
}

/*!
 * \brief minimumPushes - Вы получили строковое слово, содержащее строчные английские буквы.
 * Телефонные клавиатуры имеют клавиши, отображаемые различными наборами строчных английских
 * букв, которые можно использовать для формирования слов, толкая их. Например, ключ 2
 * сопоставляется с [«a», «b», «c»], нам нужно нажать клавишу один раз, чтобы ввести «a», два
 * раза, чтобы ввести «b», и три раза, чтобы ввести «c». Допускается перекомпоновка ключей,
 * пронумерованных от 2 до 9, в отдельные наборы букв. Ключи могут быть сопоставлены с любым
 * количеством букв, но каждая буква должна быть сопоставлена ровно с одним ключом. Необходимо
 * найти минимальное количество нажатий клавиш для ввода строкового слова. Возвращает
 * минимальное число нажатий, необходимое для ввода слова после переопределения клавиш. Пример
 * сопоставления букв и клавиш на клавиатуре телефона приведен ниже. Обратите внимание, что 1,
 * *, # и 0 не соответствуют буквам.
 *
 * Пример 1:
 * Вход: word = «abcde»
 * Выход: 5
 * Пояснение: Переопределенная клавиатура, приведенная на изображении, обеспечивает минимальную
 * стоимость. «a» - > одно нажатие на клавишу 2 «b» - > одно нажатие на клавишу 3 «c» - > одно
 * нажатие на клавишу 4 «d» - > одно нажатие на клавишу 5 «e» - > один толчок по клавише 6 Общая
 * стоимость составляет 1 + 1 + 1 + 1 + 1 = 5. Можно показать, что никакое другое отображение не
 * может обеспечить более низкую стоимость.
 *
 * Пример 2:
 * Вход: word = «xyzxyzxyzxyz»
 * Выход: 12
 * Пояснение: Переопределенная клавиатура, приведенная на изображении, обеспечивает минимальную
 * стоимость. «x» - > одно нажатие на клавишу 2 «y» - > одно нажатие на клавишу 3 «z» - > одно
 * нажатие на клавишу 4 Общая стоимость составляет 1 * 4 + 1 * 4 + 1 * 4 = 12 Можно показать,
 * что никакое другое отображение не может обеспечить более низкую стоимость. Обратите внимание,
 * что ключ 9 не сопоставляется ни с одной буквой: не обязательно сопоставлять буквы с каждой
 * клавишей, а сопоставлять все буквы.
 *
 * Пример 3:
 * Вход: word = «aabbcccddeeffghhiiiiii»
 * Выход: 24
 * Пояснение: Переопределенная клавиатура, приведенная на изображении, обеспечивает минимальную
 * стоимость. «a» - > одно нажатие на клавишу 2 «b» - > одно нажатие на клавишу 3 «c» - > одно
 * нажатие на клавишу 4 «d» - > одно нажатие на клавишу 5 «e» - > один толчок по клавише 6 «f» -
 * > одно нажатие на клавишу 7 «g» - > одно нажатие на клавишу 8 «h» - > два нажатия на клавишу
 * 9 «i»
 * - > одно нажатие на клавишу 9 Общая стоимость - 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2
 * + 1 * 2 + 2 * 2 + 6 * 1 = 24. Можно показать, что никакое другое отображение не может
 * обеспечить более низкую стоимость.
 *
 * Ограничения:
 * 1 <= word.length <= 10^5
 * слово состоит из строчных английских букв.
 */
int minimumPushes(string word)
{
    std::array<int, 26> arr = {0};
    for (const char c : word) {
        ++arr[c - 'a'];
    }
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    int ans = 0;
    for (int i = 0; i < 26; ++i) {
        ans += arr[i] * ((i / 8) + 1);
    }
    return ans;
}

/*!
 * \brief countTrapezoids - Вам задан двумерный целочисленный массив точек,
 * где точки[i] = [xi,yi] представляют координаты i-й точки на декартовой плоскости.
 * Горизонтальная трапеция - это выпуклый четырехугольник, по крайней мере, с одной парой
 * горизонтальных сторон (т.е. параллельных оси x). Две прямые параллельны тогда и только тогда,
 * когда они имеют одинаковый наклон. Возвращает количество уникальных горизонтальных трапеций,
 * которые можно сформировать, выбрав любые четыре различные точки из множества точек. Поскольку
 * ответ может быть очень большим, верните его по модулю 10^9 + 7.
 */
int countTrapezoids(vector<vector<int>> &points)
{
    unordered_map<int, int> cnt;
    for (const auto &p : points) {
        ++cnt[p[1]];
    }

    long long ans = 0, s = 0;
    for (const auto &[_, v] : cnt) {
        long long t = (static_cast<long long>(v) * (v - 1)) >> 1;
        ans = (ans + s * t) % MOD;
        s += t;
    }
    return ans;
}

}
