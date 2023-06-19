#include <iostream>
#include <stack>
#include <stdexcept>

bool stringIsFloat(std::string s) {
  int cnt = 0, 
  countDot = 0,
  countMinus = 0;

  for (int i = 0; i < s.length(); i++) {
    if (isdigit(s[i]) || s[i] == '.' || s[i] == '-') {
      cnt++;
      if (s[i] == '.') { countDot++; }
      if (s[i] == '-') { countMinus++; }
    }
  }

  if (s.length() == cnt && 
  countDot <= 1 &&
  ((countMinus == 1 && s[0] == '-' && s.length() != 1) || countMinus == 0) ) { 
    return true; 
  }
  return false;
}

bool good(std::string s) {
  std::string tmp = "";

  //counts all spaces in getline
  int cnt = 0;
  
  //counts every char to check if nuff operations
  int cntChar = 0;

  for (int i = 0; i < s.length(); i++) {
    if (s[i] != ' ') { tmp += s[i]; }

    if (s[i] == ' ' || i + 1 == s.length()) {
      cnt++;

      if (stringIsFloat(tmp)) { 
        tmp = "";
        continue;
      } else if (cnt >= 2 && (
        tmp[0] == '+' ||
        tmp[0] == '-' ||
        tmp[0] == '*' ||
        tmp[0] == '/' )) {
          tmp = "";
          cntChar++;
          continue;
        } else {
          return false;
        }
    }
  }

  //prevent core dump
  if (cntChar == 0) {
    return false;
  } else if (cnt/cntChar == 2) {
    return true;
  }
  return false;
}

double calcRPN(std::string s) {
  std::stack<double> container;
  std::string tmp;
  double out, holder, kurwa;

  for (int i = 0; i < s.length(); i++) {
    if (s[i] != ' ') { tmp += s[i]; }
    
    if (s[i] == ' ' || i + 1 == s.length()) { 
      if (stringIsFloat(tmp)) {
        container.push(std::stod(tmp));
        tmp = "";
        continue;
      } else {
        holder = container.top();
        container.pop();
        out = container.top();
        container.pop();

        switch (tmp[0]) {
          case '+':
            container.push(out + holder);
            break;
          case '-':
            container.push(out - holder);
            break;
          case '*':
            container.push(out * holder);
            break;
          case '/':
            container.push(out / holder);
            break;
        }
      }
      tmp = "";
    }
  }

  return container.top();
}


int main() {
  std::string LINE = "3 2 + 5 / 4 -";

  while (true) {
    std::getline(std::cin, LINE);

    if (good(LINE)) { break; }
  }

  std::cout << calcRPN(LINE);

  return 1;
}
