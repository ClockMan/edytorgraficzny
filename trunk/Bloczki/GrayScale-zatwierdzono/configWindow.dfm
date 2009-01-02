object cfgWindow: TcfgWindow
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Config'
  ClientHeight = 189
  ClientWidth = 296
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 281
    Height = 137
    Caption = 'Skala szaro'#347'ci'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object GreyScale: TRadioButton
      Left = 40
      Top = 32
      Width = 113
      Height = 17
      Caption = 'Pe'#322'na skala szaro'#347'ci'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      TabStop = True
      OnClick = GreyScaleClick
    end
    object GreyBalance: TRadioButton
      Left = 40
      Top = 64
      Width = 161
      Height = 17
      Caption = 'Balans odcieni szaro'#347'ci (2-50)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = GreyBalanceClick
    end
    object EditLimit: TEdit
      Left = 232
      Top = 87
      Width = 33
      Height = 21
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnChange = EditLimitChange
    end
    object TrackLimit: TTrackBar
      Left = 3
      Top = 87
      Width = 223
      Height = 45
      Enabled = False
      Max = 50
      Min = 2
      Position = 2
      TabOrder = 3
      OnChange = TrackLimitChange
    end
  end
  object OK: TButton
    Left = 48
    Top = 151
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = OKClick
  end
  object Cancel: TButton
    Left = 167
    Top = 151
    Width = 75
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 2
    OnClick = CancelClick
  end
end
