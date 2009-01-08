object cfgWin: TcfgWin
  Left = 383
  Top = 258
  BorderStyle = bsSizeToolWin
  Caption = 'Binarization config'
  ClientHeight = 192
  ClientWidth = 321
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Binarization: TGroupBox
    Left = 8
    Top = 8
    Width = 305
    Height = 178
    Caption = 'Binarization'
    TabOrder = 0
    object OK: TButton
      Left = 132
      Top = 143
      Width = 75
      Height = 25
      Caption = 'OK'
      TabOrder = 0
      OnClick = OKClick
    end
    object Anuluj: TButton
      Left = 213
      Top = 143
      Width = 75
      Height = 25
      Caption = 'Anuluj'
      TabOrder = 1
      OnClick = AnulujClick
    end
    object limitB: TTrackBar
      Left = 16
      Top = 87
      Width = 225
      Height = 50
      Ctl3D = True
      Constraints.MaxWidth = 255
      Max = 255
      ParentCtl3D = False
      TabOrder = 2
      OnChange = limitBChange
    end
    object limitBShow: TEdit
      Left = 247
      Top = 87
      Width = 41
      Height = 21
      TabOrder = 3
      OnChange = limitBShowChange
    end
    object BinarizationBalance: TRadioButton
      Left = 24
      Top = 56
      Width = 201
      Height = 17
      Caption = 'Binaryzacja progowa (0-255)'
      TabOrder = 4
      OnClick = BinarizationBalanceClick
    end
    object StandardBinarization: TRadioButton
      Left = 24
      Top = 33
      Width = 279
      Height = 17
      Caption = 'Binaryzacja standartowa (obraz monochromatyczny)'
      Checked = True
      TabOrder = 5
      TabStop = True
      OnClick = BinarizationClick
    end
  end
end
