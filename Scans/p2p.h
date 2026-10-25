#ifndef SSFW_P2P
#define SSFW_P2P

#include <windows.h>

#define P2P_COUNT 35
const char P2P_NAMES[P2P_COUNT + 1][32] = {"aMule", "Ares Galaxy", "BearShare", "BitComet", "BitTornado", "BitTorrent", "Blubster", "Cabos", "DC++", "eDonkey2000", "eMule", "ExoSee", "Free Download Manager", "FrostWire", "gtk-gnutella", "iMesh", "Kazaa", "Kazaa Lite", "KCeasy", "LimeWire", "Manolito", "Morpheus", "Kommute", "Nodezilla", "Piolet", "Retroshare", "Shareaza", "SoMud", "StealthNet", "Soulseek", "TrustyFiles", "�Torrent", "Vuze", "Warez P2P", "WinMX"};
const char P2P_KEYS[P2P_COUNT + 1][64] = {"aMule", "Ares", "BearShare", "BitComet", "BitTornado", "BitTorrent", "Blubster", "{D27928E5-C1A2-47B1-9834-6191D3AC34CE}", "DC++", "eDonkey2000", "eMule", "ExoSee", "Free Download Manager", "FrostWire", "gtk-gnutella", "iMesh", "Kazaa", "Kazaa Lite", "KCeasy", "LimeWire", "Manolito", "Morpheus", "Kommute", "NodezillaAgent", "Piolet", "Retroshare", "Shareaza", "SoMud", "StealthNet", "Soulseek", "TrustyFiles", "uTorrent", "8461-7759-5462-8226", "Warez", "WinMX"};
const char P2P_DISPLAYNAMES[P2P_COUNT + 1][32] = {"aMule", "Ares", "BearShare", "BitComet", "BitTornado", "BitTorrent", "Blubster", "Cabos", "DC++", "eDonkey2000", "eMule", "ExoSee", "Free Download Manager", "FrostWire", "gtk-gnutella", "iMesh", "Kazaa", "Kazaa Lite", "KCeasy", "LimeWire", "Manolito", "Morpheus", "Kommute", "Nodezilla Agent", "Piolet", "Retroshare", "Shareaza", "SoMud", "StealthNet", "SoulSeek", "TrustyFiles", "�Torrent", "Vuze", "Warez", "WinMX"};
const char P2P_PATHS[P2P_COUNT + 1][64] = {"aMule\\amule.exe", "Ares\\Ares.exe", "BearShare Applications\\BearShare\\BearShare.exe", "BitComet\\BitComet.exe", "BitTornado\\btdownloadgui.exe", "BitTorrent\\BitTorrent.exe", "Blubster\\Blubster.exe", "Cabos\\Cabos.exe", "DC++\\DCPlusPlus.exe", "eDonkey2000\\edonkey2000.exe", "eMule\\emule.exe", "ExoSee\\ExoSee.exe", "Free Download Manager\\fdm.exe", "FrostWire 5\\FrostWire.exe", "gtk-gnutella\\gtk-gnutella.exe", "iMesh Applications\\iMesh\\iMesh.exe", "Kazaa\\Kazaa.exe", "Kazaa Lite\\khancer.exe", "KCeasy\\KCeasy.exe", "LimeWire\\LimeWire.exe", "Manolito\\Manolito.exe", "StreamCast\\Morpheus\\Morpheus.exe", "Kommute\\kommute.exe", "Nodezilla Agent\\nodezilla.exe", "Piolet\\Piolet.exe", "RetroShare\\RetroShare.exe", "Shareaza Applications\\Shareaza\\Shareaza.exe", "SoMud\\somud.exe", "StealthNet\\StealthNet.exe", "SoulseekNS\\slsk.exe", "TrustyFiles\\TrustyFiles.exe", "uTorrent\\uTorrent.exe", "Vuze\\Azureus.exe", "Warez\\Warez.exe", "WinMX Music\\WinMX Music.exe"};

typedef struct SSFWP2PLIST _SSFWP2PLIST;
typedef _SSFWP2PLIST *LPSSFWP2PLIST;

struct SSFWP2PLIST
{
	long num_p2ps;
	char **name;

	SSFWP2PLIST();
	~SSFWP2PLIST();

	void AddProgram(const char *name);
};

void ListProgramsP2P(LPSSFWP2PLIST pProgramsP2P);
bool FileExists(const char *filename);

#endif
