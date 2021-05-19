---
title: Comments on nexo-FAST v.3.2
date: 2021-05-19
author: Aleksy Grabowski <alex.grabowski.a@gmail.com>
---

# Comments on nexo-FAST v.3.2

Most of the comments are *also* applicable to the latest 3.3 version.

Each comment has assinged a number indicating it's importance from the easy of
implemenation point of view. It considers ambiguity, correctnes, consistency
and size. Possible values are (1️⃣, 2️⃣, 3️⃣).

## Biased_Random_Selection_For_Online_Processing

_section 8.2.7.2.3 figure 183_

Generation of random number may fail, but Nok branch is absent

## Check_Payment_Amounts

_section 6.6.1_

It is very strange, they use ad-hoc cardholder message that is not defined in
Annex 14.1. Additionally they define single message "Transaction Aborted:
Supplementary ...", but I think it is more optimal to send two messages:
"Aborted", "Supplementary...".  If it will be shown to be a problem it can be
changed.

The flow is altered, nexo defines that if multiple conditions apply, then all
messages should be displayed in order, but this gives posibility for a
situation where attendant cancells first screen and then next screen will be
displayed.

Also they messed up nokReason handling They repeatedly write, that "Cancelled",
should be used if attendant decides to cancel Data Output, but then they
blatantly set Nok Reason to "Amount Error"!  Also they do not bother to explain
how actually those addtional Nok Reasons should be handled.

This procedure has one of the worst descriptions in the specification.

## Check_Service_Start_Conditions

_section 5.2.1 note 15-50_

If Service Start Events exactly matches one of the Minimal Start Conditions,
then exit with SATISFIED. This is against additional note in nexo-FAST v.3.2,
note 15-50, but what they have defined seems a little bit strange, because now
we must to check if each combination is allowed, and I think in practice
everybody would expect to match minimum start events exactly.

## Data_Output_Interaction

_section 12.2.3.2.1_

Specification is inconsistent in return value for Data Output Interaction it
mixes DONE and OK.

## Dates_Restriction

3️⃣ _section 8.2.6.2 figure 178_

Behavior isn't specified if Application Expiration Date is missing in E1 kernel
database.

## Exception_File_Checking

3️⃣ _section 6.6.11 note 96-10_

PAN Sequence Number is set in the Card Data and not in the Terminal Transaction
Database.

## Forcing_Transaction_Acceptance

3️⃣_section 6.4.2.3 figure 64_

Variable that can hold the result of Data Entry Interaction that indicates if
attendant accepted force transaction approval isn't specified.

## Ful_Manual_Entry_Processing

_section 9.2.5_

Specification does not define skipping CVD request if CVD is already present,
but this may be required for scenarios where transaction should go in "one
pass" without unnecessary data exchange with the SCAP (Attendant/Cardholder).

I imagine this may be useful if manual entry will be triggered by the e-comm
service (speculative assumption, because maybe e-comm should be handled somehow
completely differently from manual entry).

## Generate_Icc_Enciphered_Pin_Data

_section 8.2.14 figure 214_

Specification does not define action on error during actual encryption.

## Idle_Event_Processing

_section 5.2.1_

Checkig of g_callTms variable is not defined in any document, but it is implied
in nexo-IS v.4.0, line 826, that this kind of action may only be performed in
Idle State

## Initialise_Transaction_Database

_section 4.3.1_

In specification they initialize TTD with currency code and exponent during
Perform Service, but the require to display amount before that, eg. during
Amount Entry event. It is not possible to display it correctly without currency
code and exponent.

I initialize it here, so it will be available to the SCAP for the display even
if service is not started yet.

## Specific_Processing_Based_On_Pan

_section 8.2.3.2.1 figure 159 note 159-20_

In the specification this function never fails.

## Online_Approval_Request

_section 12.1_

Specification does not define what to do in case of a serious problem with HAP.
They define only DATA ERROR in case when HAP found some data inconsistency
while trying to send request. I have added some rules for
TerminalErrorIndicatior, so nexoid will be able to deal gracefully with
permantent failures of HAP module

Overwritting of `nokReason` in this procedure is not specified by the spec, but
it is useful, because otherwise in case of technical error in HAP terminal will
display Transaction Aborted with `nokReason == N_NONE`, which is misleading

## Pin_Entry

_section 6.6.6.2_

Flow described in the spec is brain-dead, there are a lot of duplications it
looks like the author just copy-pasted from different PIN Entry variant. It
hides similarities and doesn't highlight differences in PIN Entry variants.
That's why here it's reimplemented differently

This is insane! In the spec variable `pinBypassAllowed` is set during actual
PIN Entry! It should have done before. Procedure PIN Entry should only perform
pin entry based on some variable, and not set anyhing else.

### Pin_Entry_Done

Availability of PIN data after PIN Entry is not checked by the spec

## Process_AdditionalTrxData

_section 5.2.2 figure 18 note 18-10_

This function is really underdefined by the specification, basically in the
specification it does nothing, so int the implementation it also does nothing.

## Process_Application_Profile_Parameters

2️⃣ _section 7.4.2.6 figure 144_

Diagram in the spec falls to an infinite loop if an application profile
references itself.

Spec calls it a recursive process, but it is just iterative, not recusive.

## Process_Choice_of_Application

1️⃣ _section 5.2.2 figure 16 note 16-15_

Specification (nexo-FAST v.3.2, note 24-20) tells to set here Terminal Error
Indicator, with some vague decription stating: "When Terminal Error Indicator
is set to = true, Nok Reason is set to TECHNICAL ERROR and Terminal Error
Reason is set to an applicable value".

In this passage it is not immediatley obvious should we set Nok Reason and
Terminal Error Reason here, or it should already been set previously, or we
should set it based on some condition (like if it is not set already). Also in
the spec it is basically random, where those error reasons are set, and spec
sometimes overwrites them (which is even more relevant in real implementation,
because we have additional error reasons eg. NOT IMPLEMENTED).

That is why I have taken an approach that error related flags are switched on
as close as possible to the place of an actuall error, it means that in this
case Trusted Layer shall set those values and if underlyig SCAPI function
returns NOK and error reason is not set then it is assumed to be an Interface
Contract Violation.

This comment applies to all related places in the implementation.

## Process_Event

2️⃣ _section 5.2.2 figure 17 note 17-50_

`Process_Acept` actually can exit with REINITIALISE, but nexo-FAST ommits this.

## Process_Language_Selection

_section 5.2.2 figure 16 note 16-10_

It is defined to set `selectedLanguage` here in nexo-FAST, v.3.2, figure 23,
but in the current implementation it is expected that this value will be
already set by trusted layer.

## Process_Service_Selection

_section 5.2.2 figure 16 note 16-20_

The specification has inconsistency, it tells to set Nok Reason to TECHNICAL
ERROR, which may overwrite previously set NO PERMISSION. See comment in
`Process_Choice_of_Application`.

## Read_Records

_section 7.4.2.2_

Is it true that spec mandates to read all card records 2 times‽ 1ˢᵗ time in
7.4.2.2.1 and 2ⁿᵈ time in 8.2.3.2.4.

## Restore_Application_Profile_Defaults

_section 7.4.2.6 note 144-03_

CVC Default Amount is always set, because it has a default value 0, but it is
checked for existence in CVC Check Default Amount (6.6.4).

I did not find any mention about default values for optional tags that have
terminal as their source. So I assumed the same rules as for building DOL data.

Limit Set List is specified to be configurable "per E6 profile", because it is
referenced in nexo FAST v.3.2 table 14, but in the nexo IS v.4.0 line 1033 it
is specified that only single such template could exist

Default value for TACs is defined in EMV Book 3, section 10.7, but they are set
to default values during Terminal Action Analysis

## Set_Application_Label_Displayed

_section 7.4.2.6 figure 144 note 144-30_

Spec does not tell what to do if another technology is selected.

My interpretation of the following passage: [...] can be displayed by the
terminal [...] is to check `additionalTerminalCapabilities ->
terminalDataOutput . displayCardholder`.

"Application Label Default" does not need to be checked, because it is a
mandatory field and it wil be always present.

## Taa_Set_Default_Values

_section 8.2.8_

The specification does not define behavior in case when mandatory data elements
are missing, most certanly this should be handled by upper layer during
configuration validation, and transaction should not go so far in case of a
wrong terminal config, but in order to be more defensive this check is made
here because we have pointer dereferencing later and this may cause SEGFAULT.

## Terminal_Floor_Limit_Checking

_sectin 8.2.7.2.2_

Nexo-FAST specifies suboptimal approach where sum should be calculated even if
there is no matching previous tranaction.

They do not specify actions in case of overflow.

## Terminal_Risk_Management

_section 8.2.7.2.1 figure 181 note 181-10_

In nexo procedure `Terminal_Floor_Limit_Checking` can not fail, but in reality
it calls external HAP API, so that means that basic sanity checks has to be
performed, and it should bail-out if int case of failure.

TVR may be set in inner function.

## Try_Performing_Cvm

_section 8.2.5_

It is not mentioned that that currently selected CV Rule should be passed for
PIN request, but it is implicitly required for generation of an offline PIN
block and probably enciphered PIN data.

In note 90-40 it is required to generate proper Offline PIN block for both
Plain Text and Enciphered PIN CVMs, therefore this information should be
available for that procedure.

I can not pass it as an argument to Pin_Entry, because that procedure is called
in contexts where CV Rule is not available
(`Online_Request_Outcome_Processing`).

In spec procedure `Process_Cvm_Condition_Code` can not return Nok, but it has
Nok branch. Compare: nexo-FAST v.3.2, figure 169 and nexo-FAST v.3.2, figure
170~171.

# Comments to myself (todo)

  * item 11668 - remove
  * item 1697 - initialized data elements
  * item 14615 - analyze and remove

