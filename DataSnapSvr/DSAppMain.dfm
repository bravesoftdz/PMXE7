object frmDSAppMain: TfrmDSAppMain
  Left = 0
  Top = 0
  Caption = #28436#31034#29256#26381#21153#22120
  ClientHeight = 169
  ClientWidth = 293
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 52
    Top = 104
    Width = 72
    Height = 13
    Caption = #26381#21153#22120#29366#24577#65306
  end
  object lbDSServerState: TLabel
    Left = 130
    Top = 104
    Width = 24
    Height = 13
    Caption = #20572#27490
    Color = clRed
    ParentColor = False
  end
  object lbLastTime: TLabel
    Left = 52
    Top = 24
    Width = 110
    Height = 21
    Caption = 'lbLastTime'
    Color = clBtnFace
    Font.Charset = GB2312_CHARSET
    Font.Color = clBlue
    Font.Height = -21
    Font.Name = #23435#20307
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Button1: TButton
    Left = 200
    Top = 120
    Width = 75
    Height = 25
    Caption = #25171#24320#27983#35272#22120
    TabOrder = 0
    OnClick = Button1Click
  end
  object btGen: TButton
    Left = 8
    Top = 123
    Width = 75
    Height = 25
    Caption = 'JS'
    TabOrder = 1
    OnClick = btGenClick
  end
  object MainMenu1: TMainMenu
    Left = 220
    Top = 48
    object N1: TMenuItem
      Caption = #25991#20214
      object muExite: TMenuItem
        Caption = #36864#20986
        OnClick = pmuExitClick
      end
    end
    object N2: TMenuItem
      Caption = #24110#21161
      Visible = False
      object muAbout: TMenuItem
        Caption = #20851#20110
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object muHelp: TMenuItem
        Caption = #24110#21161
      end
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 32
    Top = 48
    object pmuExit: TMenuItem
      Caption = #36864#20986
      OnClick = pmuExitClick
    end
    object pmuRestore: TMenuItem
      Caption = #24674#22797
      OnClick = pmuRestoreClick
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 200
    Top = 8
  end
  object ProxyConnection: TSQLConnection
    ConnectionName = 'DSHTTPCONNECTION'
    DriverName = 'DataSnap'
    LoginPrompt = False
    Params.Strings = (
      'DriverUnit=Data.DBXDataSnap'
      'HostName=localhost'
      'DatasnapContext=datasnap/'
      
        'DriverAssemblyLoader=Borland.Data.TDBXClientDriverLoader,Borland' +
        '.Data.DbxClientDriver,Version=16.0.0.0,Culture=neutral,PublicKey' +
        'Token=91d62ebb5b0d1b1b'
      '//DelegateConnection=DBXTraceConnection'
      'CommunicationProtocol=http'
      'DriverName=DataSnap'
      'Port=8080'
      'Filters={}'
      'DSAuthenticationUser=FSAdmin'
      'DSAuthenticationPassword=fst123!@#'
      '=')
    Left = 128
    Top = 48
  end
end
