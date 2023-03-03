/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include <string.h>

#include "bsp_api.h"
#include "r_ethsw.h"
#include <math.h>

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

#ifndef ETHSW_ERROR_RETURN

/*LDRA_INSPECTED 77 S This macro does not work when surrounded by parentheses. */
 #define ETHSW_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif                                 /* !ETHSW_ERROR_RETURN */

/** "SWIT" in ASCII.  Used to determine if the control block is open. */
#define ETHSW_OPEN                            (0x53574954U)

/* Initial value of down counter for timeout detection */
#define ETHSW_TIMEOUT_COUNT                   (1000000000U)

/* Maximum Frame Length */
#define ETHSW_FRAME_SIZE                      (0x2408U)

/* ENABLE PORT Bit Definitions(PORT_ENA,UCAST_DEFAULT_MASK,BCAST_DEFAULT_MASK,MCAST_DEFAULT_MASK Register) */
#define ETHSW_ENABLE_PORT0                    (1UL << 0)
#define ETHSW_ENABLE_PORT1                    (1UL << 1)
#define ETHSW_ENABLE_PORT2                    (1UL << 2)
#define ETHSW_ENABLE_PORT3                    (1UL << 3)

/* COMMAND_CONFIG Register Bit Definitions */
#define ETHSW_COMMAND_CONFIG_ENA_10           (1UL << 25)
#define ETHSW_COMMAND_CONFIG_NO_LGTH_CHECK    (1UL << 24)
#define ETHSW_COMMAND_CONFIG_CNTL_FRM_ENA     (1UL << 23)
#define ETHSW_COMMAND_CONFIG_LOOP_ENA         (1UL << 15)
#define ETHSW_COMMAND_CONFIG_SW_RESET         (1UL << 13)
#define ETHSW_COMMAND_CONFIG_TX_CRC_APPEND    (1UL << 11)
#define ETHSW_COMMAND_CONFIG_HD_ENA           (1UL << 10)
#define ETHSW_COMMAND_CONFIG_TX_ADDR_INS      (1UL << 9)
#define ETHSW_COMMAND_CONFIG_PAUSE_IGNORE     (1UL << 8)
#define ETHSW_COMMAND_CONFIG_PAUSE_FWD        (1UL << 7)
#define ETHSW_COMMAND_CONFIG_CRC_FWD          (1UL << 6)
#define ETHSW_COMMAND_CONFIG_PAD_EN           (1UL << 5)
#define ETHSW_COMMAND_CONFIG_PROMIS_EN        (1UL << 4)
#define ETHSW_COMMAND_CONFIG_ETH_SPEED        (1UL << 3)
#define ETHSW_COMMAND_CONFIG_RX_ENA           (1UL << 1)
#define ETHSW_COMMAND_CONFIG_TX_ENA           (1UL << 0)

/* INT_CONFIG Register Bit Number Definitions */
#define ETHSW_INT_CONFIG_PATTERN_INT          (1UL << 31)
#define ETHSW_INT_CONFIG_TDMA_INT             (1UL << 30)
#define ETHSW_INT_CONFIG_TSM_INT              (1UL << 29)
#define ETHSW_INT_CONFIG_IRQ_LNK_SHIFT        (8U)
#define ETHSW_INT_CONFIG_IRQ_LNK_MASK         (0x7 << ETHSW_INT_CONFIG_IRQ_LNK_SHIFT)
#define ETHSW_INT_CONFIG_DLR_INT              (1UL << 5)
#define ETHSW_INT_CONFIG_IRQ_EN               (1UL << 0)

#define ETHSW_HEX_000000FF                    (0x000000ffU)
#define ETHSW_HEX_0000FF00                    (0x0000ff00U)
#define ETHSW_HEX_00FF0000                    (0x00ff0000U)
#define ETHSW_HEX_FF000000                    (0xff000000U)
#define ETHSW_HEX_0000FFFF                    (0x0000ffffU)
#define ETHSW_DEC_100                         (100U)
#define ETHSW_DEC_512                         (512U)
#define ETHSW_DEC_1000                        (1000U)

#define ETHSW_HOST_PORT_NUMBER                (3U)
#define ETHSW_PORT_COUNT                      (3U) ///< Number of External port
#define ETHSW_PORT_COUNT_ALL                  (4U) ///< Number of All port (include managemant port)

/* Bit Mask for register access */
#define ETHSW_1BIT_MASK                       (0x1U)
#define ETHSW_2BITS_MASK                      (0x3U)
#define ETHSW_3BITS_MASK                      (0x7U)
#define ETHSW_4BITS_MASK                      (0xfU)
#define ETHSW_9BITS_MASK                      (0x1ffU)
#define ETHSW_12BITS_MASK                     (0xfffU)

/* LK_CTRL Register Bit Definitions */
#define ETHSW_LK_MASK                         (0x9E)
#define ETHSW_LK_PERVLAN                      (7)
#define ETHSW_LK_DISCUNKN                     (4)
#define ETHSW_LK_MIGRAT                       (3)
#define ETHSW_LK_AGING                        (2)
#define ETHSW_LK_LEARN                        (1)
#define ETHSW_LK_ADDR_CLEAR                   (1 << 29)
#define ETHSW_LK_ADDR_LOOKUP                  (1 << 28)
#define ETHSW_LK_ADDR_VALID                   (1)
#define ETHSW_LK_ADDR_WRITE                   (1 << 25)
#define ETHSW_LK_ADDR_REG_VALID               (1 << 16)
#define ETHSW_LK_ADDR_REG_TYPE                (1 << 17)
#define ETHSW_LK_ADDR_PORTMASK                (0xF << 21)
#define ETHSW_LK_ADDR_PRIOMASK                (0x7 << 18)
#define ETHSW_LK_ADDR_PORT_OFFSET             (5)
#define ETHSW_LK_ADDR_PORT_REG_OFFSET         (21)
#define ETHSW_LK_ADDR_PRIO_REG_OFFSET         (18)
#define ETHSW_LK_ADDR_MASKANDFLAGS_MASK       (0xFFFFU << 16)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

typedef union
{
    ethsw_mac_addr_t mac_addr;         /* MAC address                                  */
    uint32_t         reg_data[2];      /* datas for LK_DATA_LO and LK_DATA_HI register */
} ethsw_mac_addr_reg_t;

/** MAC table entry(for register access) */
typedef struct st_ethsw_mactab_entry_reg
{
    ethsw_mac_addr_t mac;              ///< MAC address
    uint16_t         mask_and_flags;   ///< Port bit mask and flags
} ethsw_mactab_entry_reg_t;

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static void ethsw_enable_icu(ethsw_instance_ctrl_t * const p_instance_ctrl);

static void ethsw_disable_icu(ethsw_instance_ctrl_t * const p_instance_ctrl);

void ethsw_isr_intr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

#if defined(__GNUC__)

/* This structure is affected by warnings from a GCC compiler bug. This pragma suppresses the warnings in this
 * structure only.*/

/*LDRA_INSPECTED 69 S */
 #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

/** ETHER SWITCH HAL module version data structure */
const fsp_version_t module_version =
{
    .api_version_minor  = ETHSW_API_VERSION_MINOR,
    .api_version_major  = ETHSW_API_VERSION_MAJOR,
    .code_version_major = ETHSW_CODE_VERSION_MAJOR,
    .code_version_minor = ETHSW_CODE_VERSION_MINOR
};

/** ETHER SWITCH HAL API mapping for Ethernet Controller interface */
/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const ethsw_api_t g_ethsw_on_ethsw =
{
    .open       = R_ETHSW_Open,
    .close      = R_ETHSW_Close,
    .speedCfg   = R_ETHSW_SpeedCfg,
    .versionGet = R_ETHSW_VersionGet,

    /* Forwarding */
    .macTableSet     = R_ETHSW_MacTableSet,
    .macTableGet     = R_ETHSW_MacTableGet,
    .macTableConfSet = R_ETHSW_MacTableConfSet,
    .macTableClear   = R_ETHSW_MacTableClear,
    .learningSet     = R_ETHSW_LearningSet,
    .portForwardAdd  = R_ETHSW_PortForwardAdd,
    .portForwardDel  = R_ETHSW_PortForwardDel,
    .floodUnknownSet = R_ETHSW_FloodUnknownSet,
};

/*******************************************************************************************************************//**
 * @addtogroup ETHSW
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * Open the switch ports and gets it ready to pass through the frames.
 *
 * @retval  FSP_SUCCESS                 Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to ETHER SWITCH control block or configuration structure is NULL.
 * @retval  FSP_ERR_ALREADY_OPEN        Control block has already been opened or channel is being used by another
 *                                      instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_INVALID_CHANNEL     Invalid channel number is given.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Interrupt is not enabled.
 * @retval  FSP_ERR_INVALID_POINTER     Pointer to arguments are NULL.
 ***********************************************************************************************************************/
fsp_err_t R_ETHSW_Open (ethsw_ctrl_t * const p_ctrl, ethsw_cfg_t const * const p_cfg)
{
    fsp_err_t               err             = FSP_SUCCESS;
    ethsw_instance_ctrl_t * p_instance_ctrl =
        (ethsw_instance_ctrl_t *) p_ctrl;
    R_ETHSW_Type * p_reg_switch;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN((NULL != p_cfg), FSP_ERR_INVALID_POINTER);
    ETHSW_ERROR_RETURN((BSP_FEATURE_ETHSW_MAX_CHANNELS > p_cfg->channel), FSP_ERR_INVALID_CHANNEL);
    ETHSW_ERROR_RETURN((0 <= p_cfg->irq), FSP_ERR_INVALID_ARGUMENT);

    ETHSW_ERROR_RETURN((ETHSW_OPEN != p_instance_ctrl->open), FSP_ERR_ALREADY_OPEN);

    if (ETHSW_PHYLINK_ENABLE == p_cfg->phylink)
    {
        ETHSW_ERROR_RETURN((NULL != p_cfg->p_callback), FSP_ERR_INVALID_POINTER);
        ETHSW_ERROR_RETURN((NULL != p_cfg->p_context), FSP_ERR_INVALID_POINTER);
    }
#endif

    p_instance_ctrl->p_reg_switch    = (void *) R_ETHSW;
    p_instance_ctrl->p_reg_ethsw_ptp = (void *) R_ETHSW_PTP;
    p_instance_ctrl->p_reg_ethss     = (void *) R_ETHSS;

    p_reg_switch = p_instance_ctrl->p_reg_switch;

    /* Initialize configuration of Ethernet switch module. */
    p_instance_ctrl->p_switch_cfg = p_cfg;

    /* Module start */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_RESET);
    R_BSP_MODULE_START(FSP_IP_ETHSW, p_cfg->channel);
    R_BSP_ModuleResetDisable(BSP_MODULE_RESET_ETHSW);
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_RESET);

    /* set Maximum Frame Length size */
    p_reg_switch->FRM_LENGTH_P0_b.FRM_LENGTH = ETHSW_FRAME_SIZE;
    p_reg_switch->FRM_LENGTH_P1_b.FRM_LENGTH = ETHSW_FRAME_SIZE;
    p_reg_switch->FRM_LENGTH_P2_b.FRM_LENGTH = ETHSW_FRAME_SIZE;
    p_reg_switch->FRM_LENGTH_P3_b.FRM_LENGTH = ETHSW_FRAME_SIZE;

    /* Initialize COMMAND_CONFIG_p[0] Reg */
    p_reg_switch->COMMAND_CONFIG_P0 = (ETHSW_COMMAND_CONFIG_NO_LGTH_CHECK | ETHSW_COMMAND_CONFIG_TX_CRC_APPEND |
                                       ETHSW_COMMAND_CONFIG_ETH_SPEED | ETHSW_COMMAND_CONFIG_RX_ENA |
                                       ETHSW_COMMAND_CONFIG_TX_ENA);

    /* Initialize COMMAND_CONFIG_p[1] Reg */
    p_reg_switch->COMMAND_CONFIG_P1 = (ETHSW_COMMAND_CONFIG_NO_LGTH_CHECK | ETHSW_COMMAND_CONFIG_TX_CRC_APPEND |
                                       ETHSW_COMMAND_CONFIG_ETH_SPEED | ETHSW_COMMAND_CONFIG_RX_ENA |
                                       ETHSW_COMMAND_CONFIG_TX_ENA);

    /* Initialize COMMAND_CONFIG_p[2] Reg */
    p_reg_switch->COMMAND_CONFIG_P2 = (ETHSW_COMMAND_CONFIG_NO_LGTH_CHECK | ETHSW_COMMAND_CONFIG_TX_CRC_APPEND |
                                       ETHSW_COMMAND_CONFIG_ETH_SPEED | ETHSW_COMMAND_CONFIG_RX_ENA |
                                       ETHSW_COMMAND_CONFIG_TX_ENA);

    /* Initialize COMMAND_CONFIG_p[3] Reg */
    p_reg_switch->COMMAND_CONFIG_P3 = (ETHSW_COMMAND_CONFIG_NO_LGTH_CHECK | ETHSW_COMMAND_CONFIG_TX_CRC_APPEND |
                                       ETHSW_COMMAND_CONFIG_ETH_SPEED | ETHSW_COMMAND_CONFIG_RX_ENA |
                                       ETHSW_COMMAND_CONFIG_TX_ENA);

    /* Initialize PORT ENABLE Reg */
    p_reg_switch->PORT_ENA_b.RXENA =
        (ETHSW_ENABLE_PORT0 | ETHSW_ENABLE_PORT1 | ETHSW_ENABLE_PORT2 | ETHSW_ENABLE_PORT3);
    p_reg_switch->PORT_ENA_b.TXENA =
        (ETHSW_ENABLE_PORT0 | ETHSW_ENABLE_PORT1 | ETHSW_ENABLE_PORT2 | ETHSW_ENABLE_PORT3);

    /* Initialize Learning/Lookup function global configuration Reg */
    p_reg_switch->LK_CTRL            = 0;
    p_reg_switch->LK_CTRL_b.ALW_MGRT = 1;
    p_reg_switch->LK_CTRL_b.AGING_EN = 1;
    p_reg_switch->LK_CTRL_b.LEARN_EN = 1;
    p_reg_switch->LK_CTRL_b.LKUP_EN  = 1;

    /* enable Default unicast resolution */
    p_reg_switch->UCAST_DEFAULT_MASK0_b.UCASTDM =
        (ETHSW_ENABLE_PORT0 | ETHSW_ENABLE_PORT1 | ETHSW_ENABLE_PORT2 | ETHSW_ENABLE_PORT3);

    /* enable Default broadcast resolution */
    p_reg_switch->BCAST_DEFAULT_MASK0_b.BCASTDM =
        (ETHSW_ENABLE_PORT0 | ETHSW_ENABLE_PORT1 | ETHSW_ENABLE_PORT2 | ETHSW_ENABLE_PORT3);

    /* enable Default multicast resolution */
    p_reg_switch->MCAST_DEFAULT_MASK0_b.MCASTDM =
        (ETHSW_ENABLE_PORT0 | ETHSW_ENABLE_PORT1 | ETHSW_ENABLE_PORT2 | ETHSW_ENABLE_PORT3);

    /* set port in authorized state(Port 0 authentication control and configuration Reg) */
    p_reg_switch->AUTH_PORT_b[0].AUTH = 1;

    /* set port in authorized state(Port 1 authentication control and configuration Reg) */
    p_reg_switch->AUTH_PORT_b[1].AUTH = 1;

    /* set port in authorized state(Port 2 authentication control and configuration Reg) */
    p_reg_switch->AUTH_PORT_b[2].AUTH = 1;

    /* set port in authorized state(Port 3 authentication control and configuration Reg) */
    p_reg_switch->AUTH_PORT_b[3].AUTH = 1;

    /* Initialize MGMT_TAG_CONFIG Reg */
    if (ETHSW_SPECIFIC_TAG_ENABLE == p_cfg->specific_tag)
    {
        p_reg_switch->MGMT_TAG_CONFIG_b.TAGFIELD  = (uint16_t) p_cfg->specific_tag_id;
        p_reg_switch->MGMT_TAG_CONFIG_b.TYPE2_EN  = 0;
        p_reg_switch->MGMT_TAG_CONFIG_b.TYPE1_EN  = 0;
        p_reg_switch->MGMT_TAG_CONFIG_b.AL_FRAMES = 1;
        p_reg_switch->MGMT_TAG_CONFIG_b.ENABLE    = 1;
    }
    else
    {
        p_reg_switch->MGMT_TAG_CONFIG_b.ENABLE = 0;
    }

    /* Set Ethernet Switch interrupt level and enable */
    ethsw_enable_icu(p_instance_ctrl);

    if (ETHSW_PHYLINK_ENABLE == p_instance_ctrl->p_switch_cfg->phylink)
    {
        /* Set line port phy link change interrupt enable Bit (PORT0 - 2) */
        p_reg_switch->INT_CONFIG_b.IRQ_LINK = (ETHSW_ENABLE_PORT0 | ETHSW_ENABLE_PORT1 | ETHSW_ENABLE_PORT2);

        /* Set Interrupt global enable */
        p_reg_switch->INT_CONFIG_b.IRQ_EN = 1;
    }

    p_instance_ctrl->open = ETHSW_OPEN;

    return err;
}                                      /* End of function R_ETHSW_Open() */

/********************************************************************************************************************//**
 * Close the switch ports
 *
 * @retval  FSP_SUCCESS                                 Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 *
 ***********************************************************************************************************************/
fsp_err_t R_ETHSW_Close (ethsw_ctrl_t * const p_ctrl)
{
    fsp_err_t               err             = FSP_SUCCESS;
    ethsw_instance_ctrl_t * p_instance_ctrl = (ethsw_instance_ctrl_t *) p_ctrl;

    R_ETHSW_Type * p_reg_switch;

    p_reg_switch = p_instance_ctrl->p_reg_switch;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN(ETHSW_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Set line port phy link change interrupt disable Bit (PORT0 - 2) */
    p_reg_switch->INT_CONFIG_b.IRQ_LINK = 0;

    /* Set Interrupt global disable */
    p_reg_switch->INT_CONFIG_b.IRQ_EN = 0;

    /* set port in unauthorized state(Port 0 authentication control and configuration Reg) */
    p_reg_switch->AUTH_PORT_b[0].AUTH = 0;

    /* set port in unauthorized state(Port 1 authentication control and configuration Reg) */
    p_reg_switch->AUTH_PORT_b[1].AUTH = 0;

    /* set port in unauthorized state(Port 2 authentication control and configuration Reg) */
    p_reg_switch->AUTH_PORT_b[2].AUTH = 0;

    /* set port in unauthorized state(Port 3 authentication control and configuration Reg) */
    p_reg_switch->AUTH_PORT_b[3].AUTH = 0;

    /* clear Maximum Frame Length Value */
    p_reg_switch->FRM_LENGTH_P0_b.FRM_LENGTH = ETHSW_FRAME_SIZE;
    p_reg_switch->FRM_LENGTH_P1_b.FRM_LENGTH = ETHSW_FRAME_SIZE;
    p_reg_switch->FRM_LENGTH_P2_b.FRM_LENGTH = ETHSW_FRAME_SIZE;
    p_reg_switch->FRM_LENGTH_P3_b.FRM_LENGTH = ETHSW_FRAME_SIZE;

    /* Disable PORT Rx Tx */
    p_reg_switch->PORT_ENA_b.RXENA = 0U;
    p_reg_switch->PORT_ENA_b.TXENA = 0U;

    /* Disable the MAC reception function(COMMAND_CONFIG_p[1] Reg) */
    p_reg_switch->COMMAND_CONFIG_P0 = (ETHSW_COMMAND_CONFIG_NO_LGTH_CHECK | ETHSW_COMMAND_CONFIG_TX_CRC_APPEND);

    /* Disable the MAC reception function(COMMAND_CONFIG_p[2] Reg) */
    p_reg_switch->COMMAND_CONFIG_P1 = (ETHSW_COMMAND_CONFIG_NO_LGTH_CHECK | ETHSW_COMMAND_CONFIG_TX_CRC_APPEND);

    /* Disable the MAC reception function(COMMAND_CONFIG_p[2] Reg) */
    p_reg_switch->COMMAND_CONFIG_P2 = (ETHSW_COMMAND_CONFIG_NO_LGTH_CHECK | ETHSW_COMMAND_CONFIG_TX_CRC_APPEND);

    /* Disable the MAC reception function(COMMAND_CONFIG_p[3] Reg) */
    p_reg_switch->COMMAND_CONFIG_P3 = (ETHSW_COMMAND_CONFIG_NO_LGTH_CHECK | ETHSW_COMMAND_CONFIG_TX_CRC_APPEND);

    /* Disable Ethernet interrupt. */
    ethsw_disable_icu(p_instance_ctrl);

    /** Clear configure block parameters. */
    p_instance_ctrl->p_switch_cfg = NULL;

    /** Mark the channel not open so other APIs cannot use it. */
    p_instance_ctrl->open = 0U;

    return err;
}                                      /* End of function R_ETHER_Close() */

/********************************************************************************************************************//**
 * Configs speed and duplex of the port
 *
 * @retval  FSP_SUCCESS                                 Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION                           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Invalid input parameter.
 *
 ***********************************************************************************************************************/
fsp_err_t R_ETHSW_SpeedCfg (ethsw_ctrl_t * const p_ctrl, uint8_t const port, ethsw_link_speed_t const speed)
{
    ethsw_instance_ctrl_t * p_instance_ctrl = (ethsw_instance_ctrl_t *) p_ctrl;
    fsp_err_t               err             = FSP_SUCCESS;
    R_ETHSW_Type volatile * p_reg_switch;
    uint32_t volatile     * p_reg_command_config;
    uint32_t                command_config;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN(ETHSW_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_reg_switch = p_instance_ctrl->p_reg_switch;

    switch (port)
    {
        case 0:
        {
            p_reg_command_config = &p_reg_switch->COMMAND_CONFIG_P0;
            break;
        }

        case 1:
        {
            p_reg_command_config = &p_reg_switch->COMMAND_CONFIG_P1;
            break;
        }

        case 2:
        {
            p_reg_command_config = &p_reg_switch->COMMAND_CONFIG_P2;
            break;
        }

        default:
        {
            err = FSP_ERR_INVALID_ARGUMENT;
            break;
        }
    }

    if (err == FSP_SUCCESS)
    {
        command_config = *p_reg_command_config;

        command_config &= ~(ETHSW_COMMAND_CONFIG_ENA_10 |
                            ETHSW_COMMAND_CONFIG_HD_ENA |
                            ETHSW_COMMAND_CONFIG_ETH_SPEED);
        switch (speed)
        {
            case ETHSW_LINK_SPEED_10H:
            {
                command_config |= (ETHSW_COMMAND_CONFIG_ENA_10 |
                                   ETHSW_COMMAND_CONFIG_HD_ENA);
                break;
            }

            case ETHSW_LINK_SPEED_10F:
            {
                command_config |= (ETHSW_COMMAND_CONFIG_ENA_10);
                break;
            }

            case ETHSW_LINK_SPEED_100H:
            {
                command_config |= (ETHSW_COMMAND_CONFIG_HD_ENA);
                break;
            }

            case ETHSW_LINK_SPEED_100F:
            {
                break;
            }

            case ETHSW_LINK_SPEED_1000H:
            {
                command_config |= (ETHSW_COMMAND_CONFIG_HD_ENA |
                                   ETHSW_COMMAND_CONFIG_ETH_SPEED);
                break;
            }

            case ETHSW_LINK_SPEED_1000F:
            {
                command_config |= (ETHSW_COMMAND_CONFIG_ETH_SPEED);
                break;
            }

            default:
            {
                err = FSP_ERR_INVALID_ARGUMENT;
                break;
            }
        }

        *p_reg_command_config = command_config;
    }

    return err;
}                                      /* End of function R_ETHSW_ConfSpeed() */

/********************************************************************************************************************//**
 * DEPRECATED Provides API and code version in the user provided pointer.
 *
 * @retval  FSP_SUCCESS                  Version information stored in provided p_version.
 * @retval  FSP_ERR_ASSERTION            p_version is NULL.
 ***********************************************************************************************************************/
__INLINE fsp_err_t R_ETHSW_VersionGet (fsp_version_t * const p_version)
{
#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_version);
#endif

    *p_version = module_version;

    return FSP_SUCCESS;
}                                      /* End of function R_ETHSW_VersionGet() */

/*******************************************************************************************************************//**
 * Sets the static MAC address entry for the given MAC address.
 *
 * @retval  FSP_SUCCESS                 Command successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER     Pointer to arguments are NULL.
 * @retval  FSP_ERR_TIMEOUT             Timeout error
 **********************************************************************************************************************/
fsp_err_t R_ETHSW_MacTableSet (ethsw_ctrl_t * const p_ctrl, ethsw_mactab_entry_t * p_mac_tab)
{
    ethsw_mac_addr_reg_t entry = {0};
    uint64_t             timeout;      /* timeout */
    ethsw_port_mask_t    port_mask;    /* converted portmask */
    volatile uint32_t    dammy_read;

    R_ETHSW_Type volatile * p_switch_reg;
    ethsw_instance_ctrl_t * p_instance_ctrl = (ethsw_instance_ctrl_t *) p_ctrl;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN(ETHSW_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    ETHSW_ERROR_RETURN((NULL != p_mac_tab), FSP_ERR_INVALID_POINTER);
    ETHSW_ERROR_RETURN((NULL != p_mac_tab->mac_addr), FSP_ERR_INVALID_POINTER);
    ETHSW_ERROR_RETURN((NULL != *p_mac_tab->mac_addr), FSP_ERR_INVALID_POINTER);
#endif

    p_switch_reg = p_instance_ctrl->p_reg_switch;

    /* remove port_mask bit and translate host port if set */
    port_mask = p_mac_tab->port_mask & ETHSW_PORT_BITS;
    if (p_mac_tab->port_mask & ETHSW_PORT_HOST)
    {
        port_mask |= (1U << ETHSW_HOST_PORT_NUMBER);
    }

    /* copy mac address to get valid alignment */
    memcpy(entry.mac_addr, *p_mac_tab->mac_addr, ETHSW_MAC_ADDR_LEN);

    p_switch_reg->LK_DATA_LO = entry.reg_data[0];
    p_switch_reg->LK_DATA_HI = entry.reg_data[1];

    p_switch_reg->LK_DATA_HI2_b.MEMDATA = p_mac_tab->vlan_id &
                                          (R_ETHSW_LK_DATA_HI2_MEMDATA_Msk >> R_ETHSW_LK_DATA_HI2_MEMDATA_Pos);

    /* damy read */
    dammy_read = p_switch_reg->LK_DATA_LO;
    dammy_read = p_switch_reg->LK_DATA_HI;
    dammy_read = dammy_read;

    /* Delete entry? */
    if (0 == port_mask)
    {
        p_switch_reg->LK_ADDR_CTRL |= (ETHSW_LK_ADDR_CLEAR | ETHSW_LK_ADDR_LOOKUP);
    }
    else
    {
        timeout = ETHSW_TIMEOUT_COUNT;

        /* Perform lookup to get address entry */
        p_switch_reg->LK_ADDR_CTRL |= ETHSW_LK_ADDR_LOOKUP;
        while (true == p_switch_reg->LK_ADDR_CTRL_b.BUSY)
        {
            ETHSW_ERROR_RETURN((0 != timeout), FSP_ERR_TIMEOUT);
            timeout--;
        }

        /* Address is already there. Just update the port mask and priority */
        if (p_switch_reg->LK_DATA_HI & ETHSW_LK_ADDR_REG_VALID)
        {
            /* update port bit mask  */
            p_switch_reg->LK_DATA_HI &= ~(uint32_t) ETHSW_LK_ADDR_PORTMASK;
            p_switch_reg->LK_DATA_HI |= (port_mask << ETHSW_LK_ADDR_PORT_REG_OFFSET);

            /* updated priority */
            p_switch_reg->LK_DATA_HI &= ~(uint32_t) ETHSW_LK_ADDR_PRIOMASK;
            p_switch_reg->LK_DATA_HI |= (p_mac_tab->priority << ETHSW_LK_ADDR_PRIO_REG_OFFSET) & ETHSW_LK_ADDR_PRIOMASK;
        }
        else
        {
            /* New static entry to be created */
            p_switch_reg->LK_DATA_HI &= ~ETHSW_LK_ADDR_MASKANDFLAGS_MASK;
            p_switch_reg->LK_DATA_HI |= ETHSW_LK_ADDR_REG_VALID;
            p_switch_reg->LK_DATA_HI |= ETHSW_LK_ADDR_REG_TYPE;
            p_switch_reg->LK_DATA_HI |= port_mask << ETHSW_LK_ADDR_PORT_REG_OFFSET;
            p_switch_reg->LK_DATA_HI |= (p_mac_tab->priority << ETHSW_LK_ADDR_PRIO_REG_OFFSET) & ETHSW_LK_ADDR_PRIOMASK;
        }

        /* trigger MAC table write */
        p_switch_reg->LK_ADDR_CTRL |= ETHSW_LK_ADDR_WRITE;
    }

    return FSP_SUCCESS;
}                                      /* End of function R_ETHSW_MacTableSet() */

/*******************************************************************************************************************//**
 * Retrieves the port mask for the given MAC address from the static MAC table.
 *
 * @retval  FSP_SUCCESS                 Command successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER     Pointer to arguments are NULL.
 * @retval  FSP_ERR_TIMEOUT             Timeout error
 **********************************************************************************************************************/
fsp_err_t R_ETHSW_MacTableGet (ethsw_ctrl_t * const p_ctrl, ethsw_mactab_entry_t * p_mac_tab)
{
    ethsw_mac_addr_reg_t entry = {0};
    uint64_t             timeout;      /* timeout */
    volatile uint32_t    dammy_read;
    volatile uint32_t    lk_data_hi;

    ethsw_instance_ctrl_t * p_instance_ctrl = (ethsw_instance_ctrl_t *) p_ctrl;
    R_ETHSW_Type volatile * p_switch_reg;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN(ETHSW_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    ETHSW_ERROR_RETURN((NULL != p_mac_tab), FSP_ERR_INVALID_POINTER);
    ETHSW_ERROR_RETURN((NULL != p_mac_tab->mac_addr), FSP_ERR_INVALID_POINTER);
    ETHSW_ERROR_RETURN((NULL != *p_mac_tab->mac_addr), FSP_ERR_INVALID_POINTER);
#endif

    p_switch_reg = p_instance_ctrl->p_reg_switch;

    /* copy mac address to get valid alignment */
    memcpy(entry.mac_addr, *p_mac_tab->mac_addr, ETHSW_MAC_ADDR_LEN);

    p_switch_reg->LK_DATA_LO = entry.reg_data[0];
    p_switch_reg->LK_DATA_HI = entry.reg_data[1];

    p_switch_reg->LK_DATA_HI2_b.MEMDATA = p_mac_tab->vlan_id &
                                          (R_ETHSW_LK_DATA_HI2_MEMDATA_Msk >> R_ETHSW_LK_DATA_HI2_MEMDATA_Pos);

    /* damy read */
    dammy_read = p_switch_reg->LK_DATA_LO;
    dammy_read = p_switch_reg->LK_DATA_HI;
    dammy_read = dammy_read;

    timeout = ETHSW_TIMEOUT_COUNT;

    /* Perform lookup to get address entry */
    p_switch_reg->LK_ADDR_CTRL |= ETHSW_LK_ADDR_LOOKUP;
    while (true == p_switch_reg->LK_ADDR_CTRL_b.BUSY)
    {
        ETHSW_ERROR_RETURN((0 != timeout), FSP_ERR_TIMEOUT);
        timeout--;
    }

    /* Entry found? */
    lk_data_hi = p_switch_reg->LK_DATA_HI;

    if (ETHSW_LK_ADDR_REG_VALID & lk_data_hi)
    {
        p_mac_tab->port_mask = (lk_data_hi & ETHSW_LK_ADDR_PORTMASK) >> ETHSW_LK_ADDR_PORT_REG_OFFSET;

        /* if host port is set convert to host port */
        if (p_mac_tab->port_mask & (1U << ETHSW_HOST_PORT_NUMBER))
        {
            p_mac_tab->port_mask = (p_mac_tab->port_mask & ~(1U << ETHSW_HOST_PORT_NUMBER)) | ETHSW_PORT_HOST;
        }

        /* priority */
        p_mac_tab->priority = (p_switch_reg->LK_DATA_HI & ETHSW_LK_ADDR_PRIOMASK) >> ETHSW_LK_ADDR_PRIO_REG_OFFSET;
    }
    else
    {
        p_mac_tab->port_mask = 0;
    }

    return FSP_SUCCESS;
}                                      /* End of function R_ETHSW_MacTableGet() */

/*******************************************************************************************************************//**
 *  Configures the MAC learning and aging parameters of MAC table.
 *
 * @retval  FSP_SUCCESS                 Command successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER     Pointer to arguments are NULL.
 **********************************************************************************************************************/
fsp_err_t R_ETHSW_MacTableConfSet (ethsw_ctrl_t * const p_ctrl, ethsw_mactab_conf_t * p_mac_tab_cnf)
{
    uint32_t reg_val;                  /* Register value */

    ethsw_instance_ctrl_t * p_instance_ctrl = (ethsw_instance_ctrl_t *) p_ctrl;
    R_ETHSW_Type volatile * p_switch_reg;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN(ETHSW_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    ETHSW_ERROR_RETURN((NULL != p_mac_tab_cnf), FSP_ERR_INVALID_POINTER);
#endif

    p_switch_reg = p_instance_ctrl->p_reg_switch;

    reg_val  = p_switch_reg->LK_CTRL & ~((uint32_t) ETHSW_LK_MASK);
    reg_val |= ((uint32_t) p_mac_tab_cnf->learn << ETHSW_LK_LEARN) |
               ((uint32_t) p_mac_tab_cnf->aging << ETHSW_LK_AGING) |
               ((uint32_t) p_mac_tab_cnf->migration << ETHSW_LK_MIGRAT) |
               ((uint32_t) p_mac_tab_cnf->discunknown << ETHSW_LK_DISCUNKN) |
               ((uint32_t) p_mac_tab_cnf->pervlan << ETHSW_LK_PERVLAN);

    p_switch_reg->LK_CTRL = reg_val;

    return FSP_SUCCESS;
}                                      /* End of function R_ETHSW_MacTableConfSet() */

/*******************************************************************************************************************//**
 * Clears specific types of entries from the MAC table or clears the whole table.
 *
 * @retval  FSP_SUCCESS                 Command successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER     Pointer to arguments are NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid input parameter.
 * @retval  FSP_ERR_TIMEOUT             Timeout error
 **********************************************************************************************************************/
fsp_err_t R_ETHSW_MacTableClear (ethsw_ctrl_t * const p_ctrl, ethsw_mactab_clr_modes_t * p_mac_tab_clr)
{
    fsp_err_t res = FSP_ERR_TIMEOUT;   /* result */
    uint64_t  timeout;                 /* timeout */

    ethsw_instance_ctrl_t * p_instance_ctrl = (ethsw_instance_ctrl_t *) p_ctrl;
    R_ETHSW_Type volatile * p_switch_reg;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN(ETHSW_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    ETHSW_ERROR_RETURN((NULL != p_mac_tab_clr), FSP_ERR_INVALID_POINTER);
#endif

    p_switch_reg = p_instance_ctrl->p_reg_switch;

    timeout = ETHSW_TIMEOUT_COUNT;

    switch (*p_mac_tab_clr)
    {
        case ETHSW_MACTAB_CLR_ALL:
        {
            p_switch_reg->LK_CTRL_b.CLRTBL = true;

            while (true == p_switch_reg->LK_CTRL_b.CLRTBL)
            {
                ETHSW_ERROR_RETURN((0 != timeout), FSP_ERR_TIMEOUT);
                timeout--;
            }

            res = FSP_SUCCESS;
            break;
        }

        case ETHSW_MACTAB_CLR_DYNAMIC:
        {
            p_switch_reg->LK_ADDR_CTRL_b.CLR_DYNAMIC = true;

            while (true == p_switch_reg->LK_ADDR_CTRL_b.CLR_DYNAMIC)
            {
                ETHSW_ERROR_RETURN((0 != timeout), FSP_ERR_TIMEOUT);
                timeout--;
            }

            res = FSP_SUCCESS;
            break;
        }

        case ETHSW_MACTAB_CLR_STATIC:
        {
            p_switch_reg->LK_ADDR_CTRL_b.CLR_STATIC = true;

            while (true == p_switch_reg->LK_ADDR_CTRL_b.CLR_STATIC)
            {
                ETHSW_ERROR_RETURN((0 != timeout), FSP_ERR_TIMEOUT);
                timeout--;
            }

            res = FSP_SUCCESS;
            break;
        }

        default:
        {
            res = FSP_ERR_INVALID_ARGUMENT;
            break;
        }
    }

    return res;
}                                      /* End of function R_ETHSW_MacTableClear() */

/*******************************************************************************************************************//**
 * Sets learning state for the given port.
 *
 * @retval  FSP_SUCCESS                 Command successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid input parameter.
 **********************************************************************************************************************/
fsp_err_t R_ETHSW_LearningSet (ethsw_ctrl_t * const p_ctrl, uint32_t port, bool enable)
{
    ethsw_instance_ctrl_t * p_instance_ctrl = (ethsw_instance_ctrl_t *) p_ctrl;
    R_ETHSW_Type          * p_switch_reg;
    uint32_t                port_num;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN(ETHSW_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    ETHSW_ERROR_RETURN((ETHSW_PORT_COUNT_ALL > (port & ~ETHSW_PORT_HOST)), FSP_ERR_INVALID_ARGUMENT);
#endif

    p_switch_reg = p_instance_ctrl->p_reg_switch;

    port_num = (port & ETHSW_PORT_HOST) ? ETHSW_HOST_PORT_NUMBER : port;

    /* set learning state */
    if (true == enable)
    {
        p_switch_reg->INPUT_LEARN_BLOCK_b.LEARNDIS &= ~(1U << port_num) & ETHSW_4BITS_MASK;
    }
    else
    {
        p_switch_reg->INPUT_LEARN_BLOCK_b.LEARNDIS = (p_switch_reg->INPUT_LEARN_BLOCK_b.LEARNDIS | (1U << port_num)) &
                                                     ETHSW_4BITS_MASK;
    }

    return FSP_SUCCESS;
}                                      /* End of function R_ETHSW_LearningSet() */

/*******************************************************************************************************************//**
 * Enables the forwarding of incoming frames on a port for RSTP.
 *
 * @retval  FSP_SUCCESS                 Command successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid input parameter.
 **********************************************************************************************************************/
fsp_err_t R_ETHSW_PortForwardAdd (ethsw_ctrl_t * const p_ctrl, uint32_t port)
{
    uint32_t block;                    /* register value */
    uint32_t tx;                       /* register value */

    ethsw_instance_ctrl_t * p_instance_ctrl = (ethsw_instance_ctrl_t *) p_ctrl;
    R_ETHSW_Type volatile * p_switch_reg;
    uint32_t                port_num;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN(ETHSW_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    ETHSW_ERROR_RETURN((ETHSW_PORT_COUNT_ALL > (port & ~ETHSW_PORT_HOST)), FSP_ERR_INVALID_ARGUMENT);
#endif

    p_switch_reg = p_instance_ctrl->p_reg_switch;

    port_num = (port & ETHSW_PORT_HOST) ? ETHSW_HOST_PORT_NUMBER : port;

    block  = p_switch_reg->INPUT_LEARN_BLOCK_b.BLOCKEN;
    block &= ~(1U << port_num);

    tx  = p_switch_reg->PORT_ENA_b.TXENA;
    tx |= (1U << port_num);

    p_switch_reg->INPUT_LEARN_BLOCK_b.BLOCKEN = block & ETHSW_4BITS_MASK;

    p_switch_reg->PORT_ENA_b.TXENA = tx & ETHSW_4BITS_MASK;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Disables the forwarding of incoming frames on a port for RSTP
 *
 * @retval  FSP_SUCCESS                 Command successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT    Invalid input parameter.
 **********************************************************************************************************************/
fsp_err_t R_ETHSW_PortForwardDel (ethsw_ctrl_t * const p_ctrl, uint32_t port)
{
    uint32_t block;                    /* register value */
    uint32_t tx;                       /* register value */

    ethsw_instance_ctrl_t * p_instance_ctrl = (ethsw_instance_ctrl_t *) p_ctrl;
    R_ETHSW_Type volatile * p_switch_reg;
    uint32_t                port_num;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN(ETHSW_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    ETHSW_ERROR_RETURN((ETHSW_PORT_COUNT_ALL > (port & ~ETHSW_PORT_HOST)), FSP_ERR_INVALID_ARGUMENT);
#endif

    p_switch_reg = p_instance_ctrl->p_reg_switch;

    port_num = (port & ETHSW_PORT_HOST) ? ETHSW_HOST_PORT_NUMBER : port;

    block  = p_switch_reg->INPUT_LEARN_BLOCK_b.BLOCKEN;
    block |= (1U << port_num);

    tx  = p_switch_reg->PORT_ENA_b.TXENA;
    tx &= ~(1U << port_num);

    p_switch_reg->INPUT_LEARN_BLOCK_b.BLOCKEN = block & ETHSW_4BITS_MASK;

    p_switch_reg->PORT_ENA_b.TXENA = tx & ETHSW_4BITS_MASK;

    return FSP_SUCCESS;
}                                      /* End of function R_ETHSW_PortForwardAdd() */

/*******************************************************************************************************************//**
 * Set the flood domain port masks for frames with unknown destinations
 *
 * @retval  FSP_SUCCESS                 Command successfully.
 * @retval  FSP_ERR_ASSERTION           Pointer to ETHER control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN            The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER     Pointer to arguments are NULL.
 **********************************************************************************************************************/
fsp_err_t R_ETHSW_FloodUnknownSet (ethsw_ctrl_t * const p_ctrl, ethsw_flood_unk_conf_t * p_flood_unk_conf)
{
    uint32_t reg;                      /* value */

    ethsw_instance_ctrl_t * p_instance_ctrl = (ethsw_instance_ctrl_t *) p_ctrl;
    R_ETHSW_Type volatile * p_switch_reg;

#if (ETHSW_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(p_instance_ctrl);
    ETHSW_ERROR_RETURN(ETHSW_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    ETHSW_ERROR_RETURN((NULL != p_flood_unk_conf), FSP_ERR_INVALID_POINTER);
#endif

    p_switch_reg = p_instance_ctrl->p_reg_switch;

    reg = p_flood_unk_conf->port_mask_bcast;
    if (reg & ETHSW_PORT_HOST)
    {
        reg &= ~ETHSW_PORT_HOST;
        reg |= ETHSW_PORT_BIT(ETHSW_HOST_PORT_NUMBER);
    }

    p_switch_reg->BCAST_DEFAULT_MASK0_b.BCASTDM = reg &
                                                  (R_ETHSW_BCAST_DEFAULT_MASK0_BCASTDM_Msk >>
                                                   R_ETHSW_BCAST_DEFAULT_MASK0_BCASTDM_Pos);

    reg = p_flood_unk_conf->port_mask_mcast;
    if (reg & ETHSW_PORT_HOST)
    {
        reg &= ~ETHSW_PORT_HOST;
        reg |= ETHSW_PORT_BIT(ETHSW_HOST_PORT_NUMBER);
    }

    p_switch_reg->MCAST_DEFAULT_MASK0_b.MCASTDM = reg &
                                                  (R_ETHSW_MCAST_DEFAULT_MASK0_MCASTDM_Msk >>
                                                   R_ETHSW_MCAST_DEFAULT_MASK0_MCASTDM_Pos);

    reg = p_flood_unk_conf->port_mask_ucast;
    if (reg & ETHSW_PORT_HOST)
    {
        reg &= ~ETHSW_PORT_HOST;
        reg |= ETHSW_PORT_BIT(ETHSW_HOST_PORT_NUMBER);
    }

    p_switch_reg->UCAST_DEFAULT_MASK0_b.UCASTDM = reg &
                                                  (R_ETHSW_UCAST_DEFAULT_MASK0_UCASTDM_Msk >>
                                                   R_ETHSW_UCAST_DEFAULT_MASK0_UCASTDM_Pos);

    return FSP_SUCCESS;
}                                      /* End of function R_ETHSW_FloodUnknownSet() */

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHSW)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Interrupt handler for Ethernet switch.
 * Supports the interrupts for DLR, PHY link change, TSM(Timestamping) and TDMA.
 *
 * @retval      none
 **********************************************************************************************************************/
void ethsw_isr_intr (void)
{
    ethsw_callback_args_t callback_arg;
    uint32_t              ulInt_Stat_Ack_Val;
    R_ETHSW_Type        * p_reg_switch;
    volatile uint32_t     dammy_read;

    IRQn_Type               irq             = R_FSP_CurrentIrqGet();
    ethsw_instance_ctrl_t * p_instance_ctrl =
        (ethsw_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    p_reg_switch = p_instance_ctrl->p_reg_switch;

    ulInt_Stat_Ack_Val = p_reg_switch->INT_STAT_ACK;

    /* Clear IRQ_LINK Interrupt */
    p_reg_switch->INT_STAT_ACK = ulInt_Stat_Ack_Val;

    /* Dammy read for Countermeasure when the CPU clock is 400 or 800MHz */
    dammy_read = p_reg_switch->INT_STAT_ACK;
    dammy_read = dammy_read;

    /* Callback : Interrupt handler */
    if ((0 != (ulInt_Stat_Ack_Val & ETHSW_INT_CONFIG_IRQ_LNK_MASK)) &&
        (ETHSW_PHYLINK_ENABLE == p_instance_ctrl->p_switch_cfg->phylink))
    {
        callback_arg.channel = p_instance_ctrl->p_switch_cfg->channel;

        callback_arg.status_link  = p_reg_switch->STATUS_P0_b.PHYLINK;
        callback_arg.status_link |= (uint32_t) (p_reg_switch->STATUS_P1_b.PHYLINK << 1);
        callback_arg.status_link |= (uint32_t) (p_reg_switch->STATUS_P2_b.PHYLINK << 2);

        callback_arg.event     = ETHSW_EVENT_LINK_CHG;
        callback_arg.p_context = p_instance_ctrl->p_switch_cfg->p_context;

        (*p_instance_ctrl->p_switch_cfg->p_callback)((void *) &callback_arg);
    }
}

/*******************************************************************************************************************//**
 * Enable ICU for Ether Switcht
 *
 * @param[in]   p_instance_ctrl     pointer to control structure
 *
 * @retval      none
 **********************************************************************************************************************/
static void ethsw_enable_icu (ethsw_instance_ctrl_t * const p_instance_ctrl)
{
    /** Configure the Ethernet Switch interrupt. */
    R_BSP_IrqCfgEnable(p_instance_ctrl->p_switch_cfg->irq, p_instance_ctrl->p_switch_cfg->ipl, p_instance_ctrl);
}                                      /* End of function ethsw_enable_icu() */

/*******************************************************************************************************************//**
 * Disable ICU for Ether Switcht
 *
 * @param[in]   p_instance_ctrl     pointer to control structure
 *
 * @retval      none
 **********************************************************************************************************************/
static void ethsw_disable_icu (ethsw_instance_ctrl_t * const p_instance_ctrl)
{
    /* Get IRQ number for A5PSW_Int interrupt. */
    R_BSP_IrqDisable(p_instance_ctrl->p_switch_cfg->irq);
    R_FSP_IsrContextSet(p_instance_ctrl->p_switch_cfg->irq, NULL);
}                                      /* End of function ether_disable_icu() */
