static const char *top_left_corner     = "┏";
static const char *top_right_corner    = "┓";
static const char *bot_left_corner     = "┗";
static const char *bot_right_corner    = "┛";
static const char *vertical_dash       = "┃";
static const char *horizontal_dash     = "━";

static const char *spade    = "♠️";
static const char *heart    = "♥️";
static const char *diamond  = "♦️";
static const char *club     = "♣️";

static const char *ace      = "A";
static const char *two      = "2";
static const char *three    = "3";
static const char *four     = "4";
static const char *five     = "5";
static const char *six      = "6";
static const char *seven    = "7";
static const char *eight    = "8";
static const char *nine     = "9";
static const char *ten      = "10";
static const char *jack     = "J";
static const char *queen    = "Q";
static const char *king     = "K";

typedef struct {
    const char *suite;
    const char *mark;
    int value;
} Card;

typedef enum Suites Suites;
enum Suites {
    SPADE,
    HEART,
    DIAMOND,
    CLUB
};

typedef struct {
    Card *cards;
    int total;
} UserSession;

const char *mark(int);
const char *suite(Suites);

void * shuffle(void *, int, int, int, size_t);
void swappy(void *, void *, size_t);

void game_cycle(void);
void print_card(Card *card);
void setup();
void show_menu();