#ifndef KEYMAPPING_H
#define KEYMAPPING_H

#include <map>

class KeyModPair {
public:
  KeyModPair() {}
  KeyModPair(const char &i, const char &m) : c(i), _mods(m) {}

  char &operator=(char &i) { return c = i; }

  char operator=(char i) { return c = i; }

  operator char() { return c; }

  char mods() { return _mods; }

private:
  char c{0};
  char _mods{0};
};

typedef std::map<int, KeyModPair> Rfb2vnc;

Rfb2vnc init_mappings();
std::map<int, int> init_mods();

#endif // KEYMAPPING_H
