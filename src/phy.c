#include <net/if.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>
#include <netlink/msg.h>
#include <netlink/attr.h>

#include "nl802154.h"
#include "iwpan.h"

static int handle_page_set(struct nl802154_state *state,
			   struct nl_cb *cb,
			   struct nl_msg *msg,
			   int argc, char **argv,
			   enum id_input id)
{
	unsigned long page;
	char *end;

	if (argc < 1)
		return 1;

	/* PAGE */
	page = strtoul(argv[0], &end, 10);
	if (*end != '\0')
		return 1;

	NLA_PUT_U8(msg, NL802154_ATTR_PAGE, page);

	return 0;

nla_put_failure:
	return -ENOBUFS;
}
COMMAND(set, page, "<page>",
	NL802154_CMD_SET_PAGE, 0, CIB_PHY, handle_page_set, NULL);

static int handle_channel_set(struct nl802154_state *state,
			      struct nl_cb *cb,
			      struct nl_msg *msg,
			      int argc, char **argv,
			      enum id_input id)
{
	unsigned long channel;
	char *end;

	if (argc < 1)
		return 1;

	/* CHANNEL */
	channel = strtoul(argv[0], &end, 10);
	if (*end != '\0')
		return 1;

	NLA_PUT_U8(msg, NL802154_ATTR_CHANNEL, channel);

	return 0;

nla_put_failure:
	return -ENOBUFS;
}
COMMAND(set, channel, "<channel>",
	NL802154_CMD_SET_CHANNEL, 0, CIB_PHY, handle_channel_set, NULL);