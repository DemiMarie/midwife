#if defined(__cplusplus) &&__cplusplus >= 201103L
# define NORETURN [[noreturn]]
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
# define NORETURN _Noreturn
#elif defined(__GNUC__) && __GNUC__ > 2 ||      \
  (__GNUC__ == 2 && __GNUC_MINOR__ >= 5)
# define NORETURN __attribute__((noreturn))
#elif !defined(NORETURN)
# define NORETURN
#endif
#include <vector>
#include <string>
NORETURN bool error(const char *msg);
typedef std::vector<std::basic_string<char> > stringVector;
stringVector lexer (char *input, size_t argc, char ** argv);
NORETURN void die (const char *arg);
