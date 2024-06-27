/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup ETHER_PHY
 * @{
 **********************************************************************************************************************/

#ifndef R_ETHER_PHY_H
#define R_ETHER_PHY_H

#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ether_phy_cfg.h"
#include "r_ether_phy_api.h"
#include "r_ether_selector.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** ETHER PHY control block. DO NOT INITIALIZE.  Initialization occurs when @ref ether_phy_api_t::open is called. */
typedef struct st_ether_phy_instance_ctrl
{
    uint32_t open;                           ///< Used to determine if the channel is configured

    /* Configuration of Ethernet PHY-LSI module. */
    ether_phy_cfg_t const * p_ether_phy_cfg; ///< Pointer to initial configurations.

    /* Interface for PHY-LSI chip. */
    volatile uint32_t * p_reg_etherc;        ///< Pointer to ETHERC peripheral registers.

    /* The capabilities of the local link as PHY data */
    uint32_t local_advertise;                ///< Capabilities bitmap for local advertising.
} ether_phy_instance_ctrl_t;

/** Identify Ethernet and EtherCAT */
typedef enum e_ether_phy_port_type
{
    ETHER_PHY_PORT_TYPE_ETHERNET  = 0, ///< Ethernet
    ETHER_PHY_PORT_TYPE_ETHER_CAT = 1, ///< EtherCAT
} ether_phy_port_type_t;

/** Identify the access interface of the PHY register */
typedef enum e_ether_phy_mdio
{
    ETHER_PHY_MDIO_GMAC  = 0,          ///< GMAC
    ETHER_PHY_MDIO_ETHSW = 1,          ///< Ether switch
    ETHER_PHY_MDIO_ESC   = 2           ///< EtherCAT
} ether_phy_mdio_t;

/** PHY Speed for setting */
typedef enum e_ether_phy_speed
{
    ETHER_PHY_SPEED_10_100  = 0,       ///< 100/10Mbps      (Note:Can be specified when auto-negotiation is ON)
    ETHER_PHY_SPEED_10_1000 = 1,       ///< 1000/100/10Mbps (Note:Can be specified when auto-negotiation is ON)
    ETHER_PHY_SPEED_10      = 2,       ///< 10Mbps
    ETHER_PHY_SPEED_100     = 3,       ///< 100Mbps
    ETHER_PHY_SPEED_1000    = 4,       ///< 1000Mbps
} ether_phy_speed_t;

/** PHY Duplex for setting */
typedef enum e_ether_phy_duplex
{
    ETHER_PHY_DUPLEX_HALF = 0,         ///< Half duplex
    ETHER_PHY_DUPLEX_FULL = 1,         ///< Full duplex
} ether_phy_duplex_t;

/** PHY Auto Negotiation for setting */
typedef enum e_ether_phy_auto_negotiation
{
    ETHER_PHY_AUTO_NEGOTIATION_OFF = 0, ///< Auto Negotiation is ON
    ETHER_PHY_AUTO_NEGOTIATION_ON  = 1, ///< Auto Negotiation is OFF
} ether_phy_auto_negotiation_t;

/** Extended configuration */
typedef struct s_ether_phy_extend_cfg
{
    ether_phy_port_type_t port_type;                                     ///< Port type
    ether_phy_mdio_t      mdio_type;                                     ///< MDIO type

    ether_phy_speed_t            bps;                                    ///< PHY Speed
    ether_phy_duplex_t           duplex;                                 ///< PHY Duplex
    ether_phy_auto_negotiation_t auto_negotiation;                       ///< Auto Negotiation ON/OFF

    bsp_io_port_pin_t phy_reset_pin;                                     ///< PHY reset pin
    uint32_t          phy_reset_time;                                    ///< PHY reset assert time in millsecond

    ether_selector_instance_t * p_selector_instance;                     ///< Instance of selector driver

    void (* p_target_init)(ether_phy_instance_ctrl_t * p_instance_ctrl); ///< Pointer to callback that is called to initialize the target.
} ether_phy_extend_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ether_phy_api_t g_ether_phy_on_ether_phy;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_ETHER_PHY_Open(ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg);

fsp_err_t R_ETHER_PHY_Close(ether_phy_ctrl_t * const p_ctrl);

fsp_err_t R_ETHER_PHY_ChipInit(ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg);

fsp_err_t R_ETHER_PHY_Read(ether_phy_ctrl_t * const p_ctrl, uint32_t reg_addr, uint32_t * const p_data);

fsp_err_t R_ETHER_PHY_Write(ether_phy_ctrl_t * const p_ctrl, uint32_t reg_addr, uint32_t data);

fsp_err_t R_ETHER_PHY_StartAutoNegotiate(ether_phy_ctrl_t * const p_ctrl);

fsp_err_t R_ETHER_PHY_LinkPartnerAbilityGet(ether_phy_ctrl_t * const p_ctrl,
                                            uint32_t * const         p_line_speed_duplex,
                                            uint32_t * const         p_local_pause,
                                            uint32_t * const         p_partner_pause);

fsp_err_t R_ETHER_PHY_LinkStatusGet(ether_phy_ctrl_t * const p_ctrl);

/*******************************************************************************************************************//**
 * @} (end addtogroup ETHER_PHY)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_ETHER_PHY_H
