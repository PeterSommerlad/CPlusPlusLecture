#ifndef WIZARD_H_
#define WIZARD_H_
// redefine the following for windows' compilers, assumes -fvisibility=hidden
#define WIZARD_EXPORT_DLL __attribute__ ((visibility ("default")))
#ifdef __cplusplus
extern "C" {
#endif

typedef struct Wizard *wizard;
typedef struct Wizard const *cwizard;
typedef struct Error *error_type;

WIZARD_EXPORT_DLL
char const *error_message(error_type error);
WIZARD_EXPORT_DLL
void error_dispose(error_type error);

WIZARD_EXPORT_DLL
wizard createWizard(char const *name, error_type *out_error);
WIZARD_EXPORT_DLL
void disposeWizard(wizard toDispose);

WIZARD_EXPORT_DLL
char const *doMagic(wizard w, char const *wish, error_type *out_error);
WIZARD_EXPORT_DLL
void learnSpell(wizard w, char const *spell);
WIZARD_EXPORT_DLL
void mixAndStorePotion(wizard w, char const *potion);
WIZARD_EXPORT_DLL
char const *wizardName(cwizard w);

#ifdef __cplusplus
}
#endif
#endif /* WIZARD_H_ */
