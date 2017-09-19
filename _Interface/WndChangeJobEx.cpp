#include "StdAfx.h"
#include "WndChangeJobEx.h"
#include "DPClient.h"
#include "DPLoginClient.h"
#include "Network.h"
#include "ResData.h"
#include "defineText.h"
#include "mover.h"

extern CDPClient g_DPlay;

CWndJobChangeEx::CWndJobChangeEx()
{
}

CWndJobChangeEx::~CWndJobChangeEx()
{
	DeleteDeviceObjects();
}

BOOL CWndJobChangeEx::Initialize( CWndBase* pWndParent, DWORD dwType )
{

	if( g_pPlayer->GetLevel() == 15 || g_pPlayer->GetLevel() == 60 || ( ( g_pPlayer->GetLevel() == 120 || g_pPlayer->GetLevel() == 129 ) && g_pPlayer->GetExpPercent() == 9999 ) )
	{
		if(  g_pPlayer->GetJob() == 0 )
		{
			nJobMin = 1;
			nJobMax = 4;
			nNewLv = 15;
		}
		else if( g_pPlayer->GetJob() < MAX_EXPERT )
		{
			nJobMin = (g_pPlayer->GetJob() + 2) * 2;
			nJobMax = nJobMin + 1;
			nNewLv = 60;
		}
		else if( g_pPlayer->GetJob() < MAX_PROFESSIONAL )
		{
			nJobMin = g_pPlayer->GetJob() + 10;
			nJobMax = nJobMin;
			nNewLv = 60;
		}
		else if( g_pPlayer->GetJob() < MAX_HERO )
		{
			nJobMin = g_pPlayer->GetJob() + 8;
			nJobMax = nJobMin;
			( g_pPlayer->GetJob() < MAX_MASTER ) ? nNewLv = 121 : nNewLv = 130;
		}
		nCurJob = nJobMin;
	}else{
		nCurJob = 0;
	}
	return CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_FASTJOBCHANGE, 0, CPoint( 0, 0 ), pWndParent );
}

BOOL CWndJobChangeEx::OnChildNotify( UINT message, UINT nID, LRESULT* pLResult )
{
	switch( nID )
	{
	case WIDC_BUTTON4:
		g_DPlay.UpdateJob( nCurJob, nNewLv );
		Destroy();
		break;
	case WIDC_BUTTON2:
		if( nCurJob < nJobMax )
			nCurJob++;
		break;
	case WIDC_BUTTON3:
		if( nCurJob > nJobMin )
			nCurJob--;
		break;
	}
	return CWndNeuz::OnChildNotify( message, nID, pLResult );
}

void CWndJobChangeEx::OnDraw( C2DRender* p2DRender )
{
	char* szInfo[] = { "Error", "Mercenaries können später zu Blade oder Knight werden.",
"Acrobats können später Jester oder Ranger werden.",
"Assists können später Ringmaster oder Billposter werden.",
"Magicians können später Psykeeper oder Elementor werden.",
"<Leer>",
"Knights sind die beste Tank-Klasse im Spiel.",
"Blades sind die stärkste Schadens-Klasse im Spiel.",
"Jester sind sowohl im PvE als auch im PvP sehr gefährlich.",
"Ranger sind gut darin, auf große Reichweite zu kämpfen.",
"Der Ringmaster ist ein Supporter und Buffer.",
"Billposter sind sowohl im PvE als auch im PvP sehr gefährlich.",
"Psykeeper sind besonders gut darin, Magie gegen einzelne Ziele einzusetzen.",
"Elementoren sind besonders gut darin, Magie gegen mehrere Gegner anzuwenden.",
"<Leer>",
"<Leer>",
"Werde Master, um noch mehr Stärke zu erlangen.",
"Werde Hero, um noch mehr Stärke zu erlangen.",
/*"Templars are the third class for knights. The ultimate guardian, far more than just a meat shield. They are the epitome of defense and are the knights in shining armor legends are made of.",
"Slayers are the third class for blades. These ferocious fighters never relent on the attack, and their fury never ceases until all those that oppose them have been laid to waste at their hands.",
"Harlequins are the third class for Jesters and posses dark skills which allow them to attack from behind there foes and even vanish right in front of your eyes. The Harlequins make for a deadly class with there combo of stealth and attacks.",
"Crackshooters are the third class for Rangers and can kill from a much further distance than Rangers. They can equip the crossbow, a compact and highly lethal weapon, these ranged fighters can and will kill multiple targets.",
"Seraphs are the third class for Ringmasters. They are capable of mending any wound, big or small and can bless their companions and awaken strength, skill, and abilities few may think are possible and can even invoke the power of temporary immortality.",
"Force Masters are the third class for Billposters. All ready one of the strongest if not thee strongest class within Madrigal. The addition of the Force Master Skills brings the most welcome boost to party abilities. Any party would welcome the power's of a Force Master.",
"Mentalists are the third class for Psykeepers. These playful but graceful and fearsome magicians can manipulate the battlefield and foes to an untimely demise.",
"Arcanists are the third class for Elementors. Arcanists are experts in the art of elements and can rain down the heaven's to destroy all that lie in there way.",*/
};


	CWndButton* nJobPic = (CWndButton*)GetDlgItem( WIDC_BUTTON4 );
	CWndStatic* nJobTit = (CWndStatic*)GetDlgItem( WIDC_STATIC1 );
	CWndButton* nApply = (CWndButton*)GetDlgItem( WIDC_BUTTON1 );
	CWndButton* chk1 = (CWndButton*) GetDlgItem( WIDC_BUTTON2 );
	CWndButton* chk2 = (CWndButton*) GetDlgItem( WIDC_BUTTON3 );
	CWndText* nJobInfo = (CWndText*)GetDlgItem( WIDC_TEXT1 );
	switch( nCurJob )
	{
	case 0:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotVan.bmp" ), TRUE );
		nJobPic->EnableWindow( FALSE );
		nJobTit->SetToolTip( "You don't have the right level" );
		nApply->EnableWindow( FALSE );
		nJobTit->SetTitle( "Error" );
		chk1->EnableWindow( FALSE );
		chk2->EnableWindow( FALSE );
		return;
		break;
	case 1:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotMer.bmp" ), TRUE );
		break;
	case 2:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotArc.bmp" ), TRUE );
		break;
	case 3:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotAs.bmp" ), TRUE );
		break;
	case 4:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotMag.bmp" ), TRUE );
		break;
	case 6: case 16: case 24:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotKnight.bmp" ), TRUE );
		break;
	case 7: case 17: case 25:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotBlad.bmp" ), TRUE );
		break;
	case 8: case 18: case 26:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotJes.bmp" ), TRUE );
		break;
	case 9: case 19: case 27:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotRan.bmp" ), TRUE );
		break;
	case 10: case 20: case 28:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotRingm.bmp" ), TRUE );
		break;
	case 11: case 21: case 29:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotBillfor.bmp" ), TRUE );
		break;
	case 12: case 22: case 30:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotPsy.bmp" ), TRUE );
		break;
	case 13: case 23: case 31:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotElem.bmp" ), TRUE );
		break;
	/*case 32:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotLord.bmp" ), TRUE );
		break;
	case 33:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotStormb.bmp" ), TRUE );
		break;
	case 34:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotWindI.bmp" ), TRUE );
		break;
	case 35:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotCracks.bmp" ), TRUE );
		break;
	case 36:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotFlor.bmp" ), TRUE );
		break;
	case 37:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotForcem.bmp" ), TRUE );
		break;
	case 38:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotMent.bmp" ), TRUE );
		break;
	case 39:
		nJobPic->SetTexture(D3DDEVICE, MakePath( DIR_THEME, "SlotElel.bmp" ), TRUE );
		break;*/
	default:
		return;
		break;
	}
	nJobPic->SetToolTip( prj.m_aJob[nCurJob].szName );
	nJobTit->SetTitle( prj.m_aJob[nCurJob].szName );
	( nCurJob == nJobMax ) ? chk1->EnableWindow( FALSE ) : chk1->EnableWindow( TRUE );
	( nCurJob == nJobMin ) ? chk2->EnableWindow( FALSE ):chk2->EnableWindow( TRUE );
	if( nCurJob < MAX_PROFESSIONAL )
		nJobInfo->SetString( szInfo[nCurJob] );
	else if( nCurJob < MAX_MASTER )
		nJobInfo->SetString( szInfo[MAX_PROFESSIONAL] );
	else if( nCurJob < MAX_HERO )
		nJobInfo->SetString( szInfo[MAX_PROFESSIONAL+1] );
	else
		nJobInfo->SetString( szInfo[nCurJob - 14] );

}

void CWndJobChangeEx::OnInitialUpdate( )
{
	CWndNeuz::OnInitialUpdate(); 
	RestoreDeviceObjects();

	
	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();
	CPoint point( rectRoot.right - rectWindow.Width(), 110 );
	Move( point );
	MoveParentCenter();
}

BOOL CWndJobChangeEx::OnCommand( UINT nID, DWORD dwMessage, CWndBase *pWndBase )
{
	return CWndNeuz::OnCommand( nID, dwMessage, pWndBase );
}

HRESULT CWndJobChangeEx::RestoreDeviceObjects()
{
	CWndNeuz::RestoreDeviceObjects();
	return S_OK;
}
HRESULT CWndJobChangeEx::InvalidateDeviceObjects()
{
	CWndNeuz::InvalidateDeviceObjects();
    return S_OK;
}
HRESULT CWndJobChangeEx::DeleteDeviceObjects()
{
	CWndNeuz::DeleteDeviceObjects();
	InvalidateDeviceObjects();
	return S_OK;
}